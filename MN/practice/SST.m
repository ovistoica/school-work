function [x] = SST(A, b)
    [n, n] = size(A);
    x(n,1) = b(n,1) / A(n,n);
    for i = n-1 : 1
        x(i, 1) = (b(i, 1) - A(i, i+1:n) * x(i+1:n, 1)) / A(i,i)
    end
end
