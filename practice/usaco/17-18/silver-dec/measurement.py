from heapq import heapify, heappush, heappop

with open('measurement.in','r') as inp, open('measurement.out','w') as out:
    N,G = map(int,inp.readline().split())

    max_list = [0]
    max_sets = {0:{-1}}

    class Day:
        def __init__(self,day,id,delta):
            self.day = int(day)
            self.id = int(id)
            self.delta = - int(delta) # negate so heap can work
        def __repr__(self):
            return str({"day": self.day, "id": self.id, "delta": self.delta})

    days = []
    output = dict()
    for l in inp:
        day = Day(*l.split())
        max_sets[0].add(day.id)
        days.append(day)
        output[day.id] = 0
    days.sort(key=lambda d: d.day)
    # print('N=%d, G=%d, days=%s' % (N,G,days))

    changes = 0
    for day in days: # O(nlog(n))
        # print(max_list)
        # print(max_sets)

        pre_set = max_sets[max_list[0]]

        pre_val = output[day.id]
        post_val = pre_val + day.delta
        output[day.id] += day.delta

        if len(max_sets[pre_val]) == 1:
            del max_sets[pre_val]
        else:
            max_sets[pre_val].remove(day.id)
        if post_val in max_sets:
            max_sets[post_val].add(day.id)
        else:
            max_sets[post_val] = {day.id}
            heappush(max_list,post_val) # O(log(n))
            # max_list.sort(reverse=True)

        while max_list[0] not in max_sets:
            heappop(max_list)

        if pre_set != max_sets[max_list[0]]:
            changes += 1

    # print(max_list)
    # print(max_sets)

    print(changes,file=out)
    print(changes)
