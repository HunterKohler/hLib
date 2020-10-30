from bisect import bisect

lmap = lambda *a, **k: list(map(*a, **k))
with open('haybales.in', 'r') as inp, open('haybales.out', 'w') as out:
    n,q = map(int, inp.readline().split(' '))
    bales = [-1] + lmap(int, inp.readline().split(' '))
    bales.sort()
    baleset = {i for i in bales[1:]}
    for line in inp:
        a,b = map(int,line.split(' '))
        ans = bisect(bales,b) - bisect(bales,a) + (1 if a in baleset else 0 )
        print(ans, file=out)
