% Stoica George-Ovidiu, 322CA

Tema 1 MN - PageRank

Am modificat semnaturile functiilor Iterative si Algebraic pentru a face o
singura citire din fisier in loc de trei. Parametrii de intrare si iesire sunt
descrisi in fiecare fisier .m folosit. Citirea se face o singura data in functia
PageRank folosind functia read_data_from_file.

*Iterative:
    Am folosit versiunea ce se bazeaza pe matricea M = (K^(-1) * A). Am pus un
numar de iteratii maxime = 100. Desi din ce am citit, algoritmul converge in
aproximativ 50 de iteratii pentru 32 de milioane de pagini. R initial este un
vector coloana ce are 1/N pe fiecare pozitie. Algoritmul respecta in rest
instructiunile din descrierea temei.

*Algebraic:
    Gram-Schmidt:
    Am folosit algoritmul Gram-Schmidt modificat pentru stabilitate numerica imbunatatita.
Algoritmul Gram-Schmidt modificat si metoda de inversare pentru R am luat-o de
aici: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.99.5150&rep=rep1&type=pdf
In loc de a folosi A_i pentru produsul scalar, se foloseste W_j.
    Algoritmul respecta instructiunile din descrierea temei.

*read_data_from_file:
    Aceasta este functia citeste fisierul de intrare si returneaza numarul de
pagini, matricea de adiacenta, inversa matricii cu gradele de iesire pe
diagonala, val1 si val2. Am folosit fclose('all') in loc de fclose(fid) pentru
ca (inca nu stiu de ce) primeam eroarea : invalid file descriptor cand apelam
fclose pe fid. Banuiesc ca undeva pe parcurs fid se modifica.
Orice informatie pe aceasta tema este binevenita.

*Apartenenta
    Pentru a calcula a si b, am facut limita inferioara cand x->val2 si 
si limita superioara cand x->val1 de unde rezulta ca:
    (1) a * val2 + b = 1; (2) a * val1 + b = 0;
    Din (1) si (2) => a = 1 / (val2 - val1); b = 1 - val2, astfel incat functia
sa fie mereu continua.

*PageRank
    In PageRank se apeleaza read_data_from_file si sunt apelate apoi cele doua
metode de calcul alei vectorului cu PageRank-uri. Am folosit insertion sort
pentru sortarea vectorului si un vector de permutari care este updatat odata cu
vectorul pentru a retine pozitiile vechilor indici din vector.

