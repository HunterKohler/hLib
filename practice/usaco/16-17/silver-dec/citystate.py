with open('citystate.in', 'r') as inp, open('citystate.out', 'w') as out:
    n = int(inp.readline())
    print(n)
    d = dict()
    for l in inp:
        k = tuple(map(lambda s: s.lower()[0:2], l.split(' ')))
        print(k)
        if k[0] != k[1]:
            if k in d:
                d[k] += 1
            else:
                d[k] = 1

    t = 0
    for k in d:
        if k[::-1] in d:
            t += d[k] * d[k[::-1]]

    print(int(t / 2), file = out)
