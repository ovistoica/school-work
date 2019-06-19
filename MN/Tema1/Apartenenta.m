% Stoica George-Ovidiu, 322CA
function y = Apartenenta(x, val1, val2)
  % Intrari:
  % -> x: PageRank-ul pentru care trebuie calculata apartenenta
  % -> val1: Limita inferioara a intervalului
  % -> val2: Limita superioara a intervalului
  % Iesiri:
  % -> y: valoarea functiei membru in punctul x. Gradul de apartenenta
  % Stim ca 0 <= x <= 1

  %Testare limite initiale
  if x < val1
    y = 0;
    return;
  end
  if x > val2
    y = 1;
    return;
  end

  %Calculez a si b bazat pe limitele superioare si inferioare
  a = 1 / (val2 - val1);
  b = 1 - val2 * a;
  %Rezultatul
  y = a * x + b;

endfunction
