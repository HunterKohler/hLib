from copy import copy

with open('rental.in','r') as inp, open('rental.out','w') as out:
    N,M,R_len = map(int,inp.readline().split())
    C = [int(inp.readline()[:-1]) for i in range(N)]
    PQ = [list(reversed(list(map(int, inp.readline().split())))) for i in range(M)]
    R = [int(inp.readline()[:-1]) for i in range(R_len)]

    C.sort(reverse=True)
    PQ.sort(reverse=True)
    R.sort(reverse=True)

    print(C)
    print(PQ)
    print(R)

    i_pq = 0
    i_r = 0
    total = 0
    for c in C:
        print(PQ)
        cowval = 0
        to_fill = c
        j_pq = i_pq
        PQ_copy = copy(PQ)
        # used = []
        # while j_pq < len(PQ) and to_fill > 0:
        #     maxmilk = min(to_fill, PQ[j_pq][1])
        #     to_fill -= maxmilk
        #     cowval += maxmilk * PQ[j_pq][0]
        #     PQ[j_pq][0] -= maxmilk
        #     if PQ[j_pq][1] == 0:
        #         j_pq += 1

        if cowval >= R[i_r]:
            i_pq = j_pq
            total += cowval
        else:
            total += R[i_r]
            i_r += 1

    print(total)
    print(total,file=out)
