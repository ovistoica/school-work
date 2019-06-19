function [G] = Jacobi_Matrix(A) 
    N = diag(diag(A));
    P = -(A -N);
    G = inv(N) * P;
endfunction
