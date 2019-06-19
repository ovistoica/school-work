function [s] = sum_funct(V)
    s = 0;
    n = input("Introduceti n");
    v1 = V(V < n);
    for i = v1(mod(v1, 2) == 1)
        s = s + i;
    endfor
endfunction
