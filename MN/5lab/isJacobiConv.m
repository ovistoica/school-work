function [rs] = isJacobiConv(A)
    rs = max(abs(eig(Jacobi_Matrix(A))));
    if sign(rs - 1) < 0
        disp('Converge');
    else 
        disp('Nu conv');
    endif
endfunction
