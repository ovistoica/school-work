A-Star(s initial , expand, h, solution)
	//initializari
    closed ← {}
    n ← new-node()
    state(n) ← s initial
    g(n) ← 0
    π(n) ← nil
    open ← { n }

    //Bucla principala
    repeat
        if open = Ø then return failure
        n ← get_best(open) with f(n) = g(n)+h(n) = min
        open ← open - {n}
        if solution(state(n)) then return build-path(n)
        else if n not in closed then
            closed ← closed U {n}
            for each s in expand(n)
                cost_from_n ← g(n) + cost(state(n), s)
                if not (s in closed U open) then
                    n' ← new-node()
                    state(n') ← s
                    π(n') ← n
                    g(n') ← cost_from_n
                    open ← open U { n'}
                else
                    n' ← get(closed U open, s)
                    if cost_from_n < g(n') then
                        π(n') ← n
                        g(n') ← cost_from_n
                        if n' in closed then
                            closed ← closed – { n'}
                            open ← open U { n'}
	    end-for
    end-repeat
