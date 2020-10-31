from queue import Queue
with open('shuffle.in','r') as inp, open('shuffle.out','w') as out:
    N = int(inp.readline())
    A = tuple(map(lambda x: int(x) - 1,inp.readline().split()))

    # print('N=%d, A=%s' % (N,A))

    sources = [0] * N
    for a in A:
        sources[a] += 1

    # print(sources)

    q = Queue()
    for i,src in enumerate(sources):
        if src == 0:
            q.put(i)

    counter = N
    while not q.empty():
        i = q.get()
        counter -= 1
        sources[A[i]] -= 1
        if sources[A[i]] == 0:
            q.put(A[i])

    # print(counter)
    print(counter, file=out)
