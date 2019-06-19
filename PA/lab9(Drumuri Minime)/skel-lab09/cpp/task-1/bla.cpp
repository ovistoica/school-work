Dijkstra(sursa, dest):
introdu sursa in Q
d[sursa] = 0
d[nod] = +∞ // pentru orice nod != sursa
P[nod] = null // pentru orice nod din V

// relaxari succesive
cat timp Q nu e vida
    u = extrage_min (Q)
    selectat(u) = true
    foreach nod in vecini[u] // (*)
        /* daca drumul de la sursa la nod prin u este mai mic decat cel curent */
        daca not selectat(nod) si d[nod] > d[u] + w[u, nod]
	    // actualizeaza distanta si parinte
            d[nod] = d[u] + w[u, nod]
            P[nod] = u
            /* actualizeaza pozitia nodului in coada prioritara */
            actualizeaza (Q,nod)

// gasirea drumului efectiv
Initializeaza Drum = {}
nod = P[dest]
cat timp nod != null
    insereaza nod la inceputul lui Drum
    nod = P[nod]
