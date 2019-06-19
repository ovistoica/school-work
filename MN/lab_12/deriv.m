function [yss] = deriv(xs, ys)
n = length(xs);

  for i = 1:n-1
    h = xs(i + 1) - xs(i);
    y = (ys(i + 1) - ys(i)) / h;
    yss(i) = y;
  endfor
  yss(n) = yss(n - 1);
  
  disp(yss / cos(xs));
endfunction
