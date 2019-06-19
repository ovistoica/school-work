function [x, step] = Jacobi(A, b, x0, tol, max_iter)
    %Verificam daca matricea converge 
    N = diag(diag(A));
    P = A - N;
    Gj = inv(N) * P;
    %Raza spectrala > 1
    rs = max(abs(eig(Gj)));
    if (rs - 1) >= eps
      printf("Matricea nu converge\n");
      x = NaN;
      step = -1;
      break;
    end
    n = lengh(b);
    x = x0;
    for step = 1:max_iter
      for i = 1:n
        val_sum = A(i, :) * x0(:);
        val_equal_ij = A(i,i) * x0(i);
        
        x(i) = b(i) - (val_sum - val_equal_ij);
        x(i) = x(i) / A(i, i);
       end
       if norm(x - x0) < tol
          break;
       end
       x0 = x;
    end
      
endfunction
