with open('cowcode.in','r') as inp, open('cowcode.out','w') as out:
    s,n = inp.readline().split(' ')
    n = int(n)
    l = len(s)

    def parse(i): # (str, index)
        if i < l:
            return s[i]
        k = l
        while k <= i:
            k *= 2

        if k == i:
            return parse(k - 1)
        else:
            return parse(i - (k >> 1) - 1)

    print(parse(n - 1), file=out)
    # print(parse(n - 1))
