ifunction [A_tr, A_sim] = aria(xs, ys) 

n = length(xs)
A_tr = A_sim = 0;

%Regula trapezelor
for i = 1:n-1
    A_tr += 
