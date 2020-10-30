avgplus = lambda a,x,n: (avg * (n - 1) + x) / n
avgminus = lambda a,x,n: (avg * (n + 1) - x) / n
with open('homework.in','r') as inp, open('homework.out','w') as out:
    N = int(inp.readline()) # 3 <= N <= 100,000 | 1 <= K <= N - 2
    S = list(map(int,inp.readline().split()))

    minval = min(S[-1], S[-2])
    avg = (S[-1] + S[-2]) / 2
    Kmax = []
    max_adj = avg
    for Kinv in (k for k in range(N) if 0 <= k < N - 2):
        K = N - 2 - Kinv
        minval = min(minval,S[K])
        avg = avgplus(avg, S[K], Kinv + 2)
        avg_adj = avgminus(avg, minval, Kinv + 1)

        if avg_adj == max_adj:
            Kmax.append(K)
        elif avg_adj > max_adj:
            Kmax = [K]
            max_adj = avg_adj

    Kmax.sort()
    for K in Kmax:
        print(K)
        print(K, file=out)
