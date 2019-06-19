function [eigValues, eigVectors] = Deflation(A, tol, max_iter)
  [n n] = size(A);
  %Copy for MPI after we found all eigValues
  C = A;
  eigValues = zeros(n, 1);
  eigVectors = zeros(n);
  for k = 1 : n - 1
   %First eigenvalue and eigenvector using MPD
   [lamb y] = MPD(A, tol, max_iter);
    %Update the solutions
    eigValues(k) = lamb;
    eigVectors(:, k) = y;
    
    %Create deflation vectori
    x = A(k,:)'/(lamb * y(k));
    
    %Create deflation matrix
    B = A - lamb * y * x';
    %Update A for next iteration
    A = B;
  end
  
  %Find last values for A
  [lamb y] = MPD(A, tol, max_iter);
  eigValues(n) = lamb;
  eigVectors(:,n) = y;
  
  %EigenVectors found with DirectPowerMethod are unstable
  %We use indirectPowerMethods for stability now that we now EigenValues
  %With miu being the eigenvalue from that position
  for k = 1:n
    [lamb y] = MPI(C, tol, max_iter, eigValues(k));
    eigVectors(:,k) = y;
  end
  
endfunction
  
    
    
    