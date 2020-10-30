def isLeq((x1,y1),(x2,y2)):
    return x1 <= x2 and y1 <= y2
def isGeq((x1,y1),(x2,y2)):
    return x1 >= x2 and y1 >= y2

with open('where.in','r') as inp, open('where.out','w') as out:
    n = int(inp.readline())
    grid = [l for l in inp]
    points = ((x,y) for x in range(n) for y in range(n))
    rects = ((a,b) for a in points for b in points if a[0] <= b[0] and a[1] <= b[1])
    ipcs = []
    for rect in rects:
        for icp in icps:
            if icp[0][0] <= rect[0][0] and icp[0][1] <= rect[0][1] and icp[1][0] >= rect[0][1]:
                all(icp[0][j] <= rect[0][j] for j in (0,1)) and all(icp[0][j[]])

        if isipc(rect):
            ipcs.add(rect)
