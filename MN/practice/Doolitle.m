function [L, U] = Doolitle(A)
    [n,n] = size(A);
    L = zeros(n);
    U = zeros(n);
    for i = 1:n
        L(i,i) = 1;
    end

    for p = 1:n
        j = p:n;
        i = p + 1 : n;
        k = 1:p-1;
        U(p, j) = A(p, j) - L(p, k) * U(k, j);
        L(i, p) = 1/ U(p,p) * (A(i, p) - L(i,k) * U(k, p));
    end
end
