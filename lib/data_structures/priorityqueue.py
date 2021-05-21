# previously member of competition-library

import heapq


class PriorityQueue:
    def __init__(self, *args):
        self.heap = []
        if len(args) > 1:
            raise Exception('PriorityQueue takes maximum one positional '
                            + 'argument')
        elif len(args) == 1:
            try:
                iterable = iter(args[0])
            except TypeError:
                raise TypeError('Argument is not iterable')
            self.put_all(iterable)

    def __getitem__(self, index):
        if index == 0:
            return self.peek()
        else:
            raise TypeError('Can only access head (index 0) of PriorityQueue')

    def put(self, obj):
        try:
            if type(obj) in {float, int}:
                heapq.heappush(self.heap, obj)
            else:
                heapq.heappush(self.heap, (obj.__priority__(), obj))
        except TypeError:
            raise Exception('Object must integral or have a (__priority__())'
                            + 'method')

    def put_all(self, iterable):
        map(self.put, iterable)

    def peek(self):
        return self.heap[0][1]

    def pop(self):
        obj = heapq.heappop(self.heap)[1]
        return obj if type(obj) in {float, int} else obj[1]

    def __iter__(self):
        return self

    def __next__(self):
        return self.pop()

    def __len__(self):
        return len(self.heap)
