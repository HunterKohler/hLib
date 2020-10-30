from itertools import product

moveset = {'P', 'H', 'S'}
wins = lambda a,b: (a == 'P' and b == 'H') or (a == 'H' and b == 'S') or (a == 'S' and b == 'P')

with open('hps.in','r') as inp, open('hps.out','w') as out:
    n = int(inp.readline())
    counts = {k:[0] * n for k in moveset}
    for i,m_f in enumerate(inp):
        m_f = m_f[0]
        for m_c in moveset:
            counts[m_c][i] = counts[m_c][i - 1] + (1 if wins(m_c, m_f) else 0)

    maxwins = 0
    # for x,a,b in ((x,a,b) for x in range(n) for a in moveset for b in moveset):
    for x,a,b in product(range(n),moveset,moveset):
        maxwins = max(maxwins, counts[a][x] + counts[b][-1] - counts[b][x])

    # print(maxwins)
    print(maxwins, file=out)
