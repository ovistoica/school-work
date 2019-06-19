Stoica George-Ovidiu
332CA
Tema2 APD

Am folosit interfata BlockingQueue pentru problema Producer Consumer si pentru
parta de Reader Writer, in functia in care Vrajitorii scriu pe canal, folosesc
un ReentrantLock care se activeaza cand este apelata functia si dezactivat cand
mesajul pus pe canal este END, astfel un vrajitor o sa puna toate mesajele sale
odata fara sa se intercaleze cu alt vrajitor.

Pentru clasa miner am folosit Synchronize pe Miner.class atunci cand se face
citirea de pe canal ca sa ma asigur ca un acelasi miner va citi doua mesaje
consecutive.

Tema a fost ok si partea de java mi-a placut. O zi buna :)
