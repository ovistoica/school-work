function [A_trap A_Simp] = integr(xs, ys)
  n = length(xs);
  h = xs(2) - xs(1);
  capete = ys(n) + ys(1);
  A_trap = h/2 * capete;
  A_Simp = h/3 * capete;
  
  for i = 2: n - 1
    A_trap = A_trap + h * ys(i);
  endfor
  
  sum_p = 0;
  sum_imp = 0;
  
  for i = 2:2:n-1
    sum_p = sum_p + ys(i);
  endfor
  
  for i = 3:2:n-2
    sum_imp = sum_imp + ys(i);
  endfor
  
  A_Simp = A_Simp + 4 * h/3 * sum_p;
  A_Simp = A_Simp + 2 * h/3 * sum_imp;
endfunction