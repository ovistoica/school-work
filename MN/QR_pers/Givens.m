function [Q R] = Givens(A)
  [m n] = size(A);
  Gt = eye(m);
  
  for k = 1: n - 1
    for l = (k + 1): m
      if A(l, k) ~= 0
        G = eye(m);
        rho = sqrt(A(k,k)^2 + A(l,k)^2);
        c = A(k,k)/rho;
        s = -A(l,k)/rho;
        G(k, k) = c;
        G(l, k) = s;
        G(k, l) = -s;
        G(l, l) = c;
        A = G * A;
        Gt = G * Gt;
      end
    end
  end
  Q = Gt';
  R = A;
end