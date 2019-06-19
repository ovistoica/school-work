function [rs] = isGSConv(A)
    N = tril(A);
    P = -(A - N);
    G = inv(N) * P;
    rs = max(abs(eig(G)));
    if sign(rs - 1) < 0
        disp('Converge');
    else 
        disp('Nu conv');
    endif
endfunction
