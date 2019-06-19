% Stoica George-Ovidiu, 322CA
function [N, A, K_i, val1, val2] = read_data_from_file(nume)
  % Functia care citeste datele din fisier si creeaza matricea de adiacenta
  % Intrari:
  % -> nume: numele fisierului de intrare
  % Iesiri:
  % -> N: Numarul de pagini date la intrare
  % -> A: Matricea de adiacenta a paginilor
  % -> K_i: Inversa matricei ce contine pe diagonala gradele de iesire pentru pagini
  % -> val1: limita inferioara a intervalului
  % -> val2: limita superiara a intervalului
  fid = fopen(nume, 'r');
  sizeN = [1, 1];
  N = fscanf(fid, '%d', sizeN);
  A = zeros(N);
  K = zeros(N);
  K_i = zeros(N);
  %Crearea matricei de adiacenta
  for i = 1:N
    node = fscanf(fid, '%d', [1, 1]);
    L_node = fscanf(fid, '%d', [1, 1]);
    neighbours = fscanf(fid, '%d', [1, L_node]);
    A(node, neighbours(:)) = 1;
    %Verificare daca este vecin cu el insusi
    for j = 1:L_node
      if neighbours(j) == node
        L_node--;
        A(node, node) = 0;
        break;
      end
    end
    % K:Matricea ce contine pe diagonala gradele de iesire pentru fiecare pagina
    K(node, node) = L_node;
  end
  %Calculez inversa lui K (matrice diagonala)
  for i = 1:N
    if K(i,i) ~= 0
      K_i(i, i) = 1 / K(i,i);
    end
  end
  %Citire val1 si val2
  val1 = fscanf(fid, '%f', [1, 1]);
  val2 = fscanf(fid, '%f', [1, 1]);
  %Primesc eroare cu fclose(fid)
  fclose( 'all' );
endfunction
