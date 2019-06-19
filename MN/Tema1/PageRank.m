% Stoica George-Ovidiu, 322CA

function [R1 R2] = PageRank(nume, d, eps)
  % Calculeaza indicii PageRank pentru cele 3 cerinte
  % Scrie fisierul de iesire nume.out
  % Intrari:
  % -> nume: numele fisierului de intrare
  % -> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
  % -> eps: eruarea care apare in algoritm.
  % Iesiri:
  % -> R1: vectorul de PageRank-uri acordat pentru fiecare pagina.

  % Setarea output cu 6 zecimale
  output_precision(6);

  %Citirea datelor din fisier
  % -> N: numar de pagini;
  % -> A: matricea de adiacenta;
  % -> K_i: inversa matricei cu gradele de iesire pe diagonala;
  % -> val1: limita inferioara interval
  % -> val2: limita superioara interval
  [N A K_i val1, val2] = read_data_from_file(nume);

  %Calcularea vectorilor de PageRand prin Iterative si Algebraic
  R1 = Iterative(N, A, K_i, d, eps);
  R2 = Algebraic(N, A, K_i, d);

  %Crearea fisierului de output
  out_file = strcat(nume, '.out');
  fid = fopen(out_file, 'w');

  %Scrierea vectorilor in fisierul de output
  fprintf(fid, '%d\n', N);
  fprintf(fid, '%.6f\n', R1);
  fprintf(fid,'\n');
  fprintf(fid, '%.6f\n', R2);
  fprintf(fid,'\n');

  %Vector de permutari pentru output Apartenenta
  for i = 1:N
    Perm(i) = i;
  end

  %Sortarea vectorului R2 folosind insertion sort
  for i = 1:N
    x = R2(i);
    j = i - 1;
    while j >= 1 && R2(j) < x
      R2(j+1) = R2(j);
      %Updatarea vectorului de permutari
      Perm(j + 1) = Perm(j);
      j = j - 1;
    end
    R2(j + 1) = x;
    Perm(j + 1) = i;
  end

  %Calcularea si Scrierea Apartenentei in fisier
  for i = 1:N
    y = Apartenenta(R2(i), val1, val2);
    fprintf(fid, '%d %d ', i, Perm(i));
    fprintf(fid,'%.6f\n', y);
  end
  fclose('all');
endfunction
