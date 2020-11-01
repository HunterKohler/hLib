START = 0
END = 1
with open('lifeguards.in','r') as inp, open('lifeguards.out','w') as out:
    N = int(inp.readline())
    # print('N = %d' % N)
    events = []
    for c,l in enumerate(inp):
        t1,t2 = map(int,l.split())
        events.append((t1,c,START))
        events.append((t2,c,END))
    events.sort(key=lambda e: e[0])

    t = 0
    t_alone =  [0] * N
    t_total = 0
    t_prev = 0
    open = set()
    i = 0
    while i < len(events):
        t = events[i][0]
        t_delta = t - t_prev
        if len(open) > 0:
            t_total += t_delta
        if len(open) == 1:
            elem = open.pop()
            t_alone[elem] += t_delta
            open.add(elem)


        # print('%d: %s' % (t,open))

        while i < len(events) and events[i][0] == t:
            t,c,e = events[i]
            if e == END:
                open.remove(c)
            else:
                open.add(c)
            i += 1
        t_prev = t

    # print(t_total, min(t_alone), t_alone, t_total - min(t_alone))
    print(t_total - min(t_alone), file=out)
