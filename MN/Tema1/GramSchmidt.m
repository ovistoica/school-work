% Stoica George-Ovidiu, 322CA

function B  = GramSchmidt(A)
  % Functia care calculeaza inversa matricii A folosind factorizari Gram-Schmidt modificat

  % Pentru stabilitate numerica se va folosi versiunea Gram-Schmidt modificata
  % Algoritmul modificat foloseste produsul scalar intre vectorii coloana w_j si
  % q_i. Inversa matricei A este R^(-1) * Q'. Computatia R^(-1) este stabila
  % numeric (vezi readme)

  [m n] = size(A);
  R = zeros(n,m);
  Q = zeros(n,m);
  for j = 1:n
    %Vector coloana intermediar pentru Q
    w = A(:, j);
    for i = 1: (j - 1)
      %R(i,j) = Produs scalar conform Modified Gram-Schmidt
      R(i,j) = sum(w .* Q(:, i));
      %Updateaza w
      w = w - R(i,j) .* Q(:,i);
    end
    %Normalizarea vectorului
    norm_w = norm(w);
    Q(:,j) = w / norm_w;
    R(j,j) = norm_w;
  end
  %Inversarea lui R
  for j = 1:n
    for i = 1:(j-1)
      R(i,j) = R(i, (1:j-1)) * R((1:j-1),j);
    end
    R((1:j-1),j) = -R((1:j-1), j) / R(j,j);
    R(j,j) = 1/R(j,j);
  end
  %Inversa lui A
  B = R * Q';

endfunction
