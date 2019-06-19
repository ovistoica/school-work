Nume: STOICA George-Ovidiu
Grupa: 332CA
Tema: Tema 1 APD

	Am citit din fisier folosind fread. Mi-am tinut matricea in memorie alocat
dinamic in forma unei matrici. Pentru grayscale este o matrice unsigned char,
iar pentru RGB, este pastrata folosind o matrice de struct rgb care este o
structura de 3 unsigned char.

*Resize:
Am paralelizat width. Width este paralelizat folosind formulele: 

	start= ceil(width / num_threads * thread_id);
	end= min((width / num_threads * (thread_id + 1)), width);

Unde width, este width al imaginii de intrare dar facut sa fie divizibil cu
resize factor astfel: 
	width = floor(width / resize_factor) * resize_factor;

Exista doua functii care fac resize. Una specifica pentru grayscale si una
pentru RGB: resizeGrayscale si resizeRGB.

Undeva exista o problema pe care inca nu am gasit-o si am petrecut mai mult de
10 ore. Looking back on it, cred ca ar fi trebuit pur si simplu sa rescriu.
Problema este ca pe 4, 8 thread-uri, pe imagini mai mari(>90 MB) rezultatul nu este cel 
asteptat. Valorile in unsigned char ale imaginii sunt cu 1 mai mari decat ar trebui (am rugat
un coleg sa imi faca resize pe imagini pentru a avea o referinta).

Pe un singur thread, aceasta problema nu este intampinata. Dar pe mai multe
thread-uri ceva ciudat se intampla. Un thread calculeaza corect, iar urmatorul
gresit. Folosind imagediff, imaginea de differenta este un zebra like pattern.

Banuieli: 
	Are de-a face cu impartirea la resize factor pentru imaginea de
output. Daca fac start si end pe width, nedivizibil cu resize_factor, o sa am
segmentation fault.

Pe imaginile primite in schelt, totul merge normal: 
	Timpi output pe cluster:
lenna_bw.pgm 

A fost o tema frumoasa. Este placut sa vezi o imagine redimensionata de codul
tau. Si am devenit cred ca de trei ori mai bun la a folosi GDB :).

 

Toate cele bune, 
Stoica Ovidiu



