from queue import Queue

sqrt = lambda x: x ** (1/2)
dist = lambda c1, c2: sqrt((c1['x'] - c2['x']) ** 2 + (c1['y'] - c2['y']) ** 2)

with open('moocast.in', 'r') as inp, open('moocast.out', 'w') as out:
    n = int(inp.readline())
    cows = [dict(zip(['x', 'y', 'r', 'adj'], list(map(int, l.split(' '))) + [[]])) for l in inp]

    for i,c1 in enumerate(cows):
        for j,c2 in enumerate(cows):
            if i != j and dist(c1, c2) <= c1['r']:
                c1['adj'] += [j]

    maxcount = 0
    for i,c in enumerate(cows):
        q = Queue()
        q.put(i)

        count = 0
        visited = [False] * n
        while not q.empty():
            j = q.get()
            if not visited[j]:
                visited[j] = True
                count += 1
                for k in cows[j]['adj']:
                    q.put(k)
        maxcount = max(maxcount, count)
        
    # print(maxcount)
    print(maxcount, file=out)
