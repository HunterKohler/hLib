from collections import deque

with open('pairup.in','r') as inp, open('pairup.out','w') as out:
    N = int(inp.readline())
    C = [list(map(int,l.split())) for l in inp]
    C.sort(key=(lambda c: c[1]))

    # print('N=%d, C=%s' % (N,C))

    maxT = 0
    i = 0
    j = N - 1
    while i <= j:
        # print(C, i, j)
        if i == j:
            maxT = max(maxT, C[i][1] * 2)
            break
        else:
            maxT = max(maxT, C[i][1] + C[j][1])

            m = min(C[i][0], C[j][0])
            C[i][0] -= m
            C[j][0] -= m

            if C[j][0] == 0:
                j -= 1
            if C[i][0] == 0:
                i += 1

    # print(maxT)
    print(maxT, file=out)
