function [x_i] = Mtangentei(x_0, tol, p, p_der, max_iter) 
    x = x_0;
    for i = 1:max_iter
        x_i = x - polyval(p, x) / polyval(polyder(p), x);
        eps = abs((x_i - x) / x_i);
        if eps < tol
            break;
        endif
        x = x_i;
        if polyval(p, x_i) == 0
            break;
        endif
    endfor
endfunction
