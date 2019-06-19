function [s] = while_sum(V)
    n = input("Introdu m: ");
    V1 = V(V < n);
    s = sum(V1(mod(V1, 2) == 1));
endfunction
