from itertools import combinations
with open('cownomics.in','r') as inp, open('cownomics.out','w') as out:
    N,M = map(int,inp.readline().split())
    spots = [[ord(c) for c in inp.readline()[:-1]] for i in range(N)] # spots[x][y]
    norms = [[ord(c) for c in inp.readline()[:-1]] for i in range(N)]

    # print('spots=%s' % spots)
    # print('norms=%s' % norms)

    counter = 0
    for X in combinations(range(M),3):
        count = True
        a = {tuple(spots[y][x] for x in X) for y in range(N)}
        for b_i in (tuple(norms[y][x] for x in X) for y in range(N)):
            if b_i in a:
                count = False
                break
        if count:
            counter += 1



    print(counter,file=out)
    # print(counter)
