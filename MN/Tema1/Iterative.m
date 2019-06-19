% Stoica George-Ovidiu, 322CA
function [R] = Iterative(N, A, K_i, d, eps)
  % Functia care calculeaza matricea R folosind algoritmul iterativ.
  % Intrari:
  % -> N: numar de pagini;
  % -> A: matricea de adiacenta;
  % -> K_i: inversa matricei cu gradele de iesire pe diagonala;
  % -> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
  % -> eps: eruarea care apare in algoritm.
  % Iesiri:
  % -> R: vectorul de PageRank-uri acordat pentru fiecare pagina.

  %Numar maxim de iteratii
  max_iter = 100;

  %Aflarea matricei M
  M = (K_i * A)';

  %Aflare R
  R_init = (1/N) * ones(N,1);
  for i = 1:max_iter
    R = (d .* M * R_init) + (((1 - d)/N) * ones(N, 1));

    %Verificare eroare sub o toleranta
    if abs(R - R_init) < eps
      %Returnarea valorii precedente
      R = R_init;
      break;
    end
    R_init = R;
  end
end
