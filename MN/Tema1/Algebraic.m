% Stoica George-Ovidiu, 322CA
function R = Algebraic(N, A, K_i, d)
  % Functia care calculeaza vectorul PageRank folosind varianta algebrica de calcul.
  % Intrari:
  % -> N: numar de pagini;
  % -> A: matricea de adiacenta;
  % -> K_i: inversa matricei cu gradele de iesire pe diagonala;
  % -> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
  % Iesiri:
  % -> R: vectorul de PageRank-uri acordat pentru fiecare pagina.
  
  %Creeaza matricea M
  M = (K_i * A)';
  %Crearea matricei pentru formula
  Mat = eye(N) - d*M;
  %Aflarea inversei lui Mat folosind Gram-Schmidt modificat
  Inv = GramSchmidt(Mat);
  %Aflarea lui R
  R = Inv * (((1-d)/N) * ones(N,1));
end
