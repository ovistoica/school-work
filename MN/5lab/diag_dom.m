function [x] = diag_dom(A) 
    [n, n] = size(A);
    for i = 1:n
        if max(abs(A(i, 1:n))) != A(i, i)
            disp('Matricea nu e diagonal dominanta');
            break;
        endif
    endfor
    if i == n
        disp('Matricea este diagonal dominanta');
    endif
endfunction
