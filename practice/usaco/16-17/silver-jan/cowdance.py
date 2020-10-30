with open('cowdance.in', 'r') as inp, open('cowdance.out', 'w') as out:
    N, T_max = map(int, inp.readline().split(' '))
    d_in = [int(i) for i in inp]
    # print('N=%d, T_max=%d, d=%s' % (N,T_max,d_in))

    def search(l,r):
        print(l,r)
        K = (l + r) // 2
        if r <= l:
            return K
        T = 0
        d = d_in[:]

        stage = d[:K]
        next = K
        while len(stage) > 0:
            stage.sort()
            T += stage[0]
            stage_next = [v - stage[0] for v in stage if v > stage[0]]
            stage = stage_next + d[next:min(next + len(stage) - len(stage_next), N)]
            next += len(stage) - len(stage_next)


        if T < T_max:
            return search(l,K - 1)
        elif T > T_max:
            return search(K + 1,r)
        else:
            return K

    K_min = search(1,N)
    print(K_min)
    print(K_min, file=out)
