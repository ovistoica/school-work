function [Q R] = Householder(A)
  [n n] = size(A);
  Q = eye(n);
  for i = 1:n-1
    %sigma
    s = sign(A(i, i)) * norm(A((i:n), i));
    
    %Zero pana la elem de pe diagonala, s si apoi continutul A de pe coloana
    v = [zeros(i-1, 1); s + A(i,i); A((i+1:n), i)];
    
    %Reflectorul Householder
    H = eye(n) - 2 * (v * v')/(v' * v);
    %A_k -> A_K+1
    A = H * A;
    %Q = H1 * H2 .. Hn
    Q = H * Q;
  end
  %Q din for e defapt Q^T
  Q = Q';
  R = A;
endfunction 