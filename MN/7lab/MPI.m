function [lamb, y, pasi] = MPI(A, tol, max_iter, u)
  [n,n] = size(A);
  y_prev = rand(n, 1);
  lamb_prev = inf;
  for k = 1:max_iter
    A_cur = A - u * eye(n);
    z = A_cur^(-1) * y_prev;
    y = z / norm(z);
    lamb = y' * A * y;
    if abs((lamb - lamb_prev)/lamb) < tol
      break;
    endif
    u = lamb;
    y_prev = y;
    lamb_prev = lamb;
  endfor
  pasi = k;
 endfunction
    