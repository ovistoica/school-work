function [x] = SSI(A, b)
    [n, n] = size(A);
    x(1, 1) = b(1, 1) / A(1, 1);
    for i = 2 : n
        x(i, 1) = (b(i, 1) - A(i,1:i-1) * x(1:i-1, 1))/A(i,i);
    end
end
