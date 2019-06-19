ctc(G = (V, E))
	S <- stiva vida
	culoare[1..n] = alb
	cat timp exista un nod v din V care nu e pe stiva
		dfs(G, v)
	culoare[1..n] = alb
	cat timp S != stiva vida
		v = pop(S)
		dfsT(GT, v) /* toate nodurile ce pot fi vizitate din v fac  parte din ctc; dupa vizitare, aceastea sunt scoase din S si din G */

dfs(G, v)
        culoare[v] = gri
        pentru fiecare (v, u) din E
        daca culoare[u] == alb
                dfs(u)
        push(S, v) // nodul este terminat de expandat, este pus pe stiva
        culoare[v] = negru

dfsT(G, v) – similar cu dfs(G, v): fara stiva, dar cu retinerea solutiei
