function [m] = Mbisectie(a, b, tol, p) 
    m = (a + b) / 2;
    eps = inf;
    while eps >= tol
        fa = polyval(p, a);
        fm = polyval(p, m);

        if fa * fm < 0
            b = m;
        endif
        if fa * fm > 0
            a = m;
        endif
        if fa * fm == 0
            break;
        endif

        m_new = (a + b) / 2;
        eps = abs((m_new - m) / m_new);

        m = m_new;

    endwhile

endfunction
