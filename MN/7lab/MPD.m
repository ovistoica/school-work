function [lamb, y, pasi] = MPD(A, tol, max_iter)
  [n,n] = size(A);
  y_prev = rand(n, 1);
  lamb_prev = inf;
  for k = 1:max_iter 
    z = A * y_prev;
    y = z / norm(z);
    lamb = y' * A * y;
    if abs((lamb - lamb_prev) / lamb) < tol
      break;
    endif
    y_prev = y;
    lamb_prev = lamb;
  endfor
  pasi = k;
 endfunction