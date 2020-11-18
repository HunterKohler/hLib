from itertools import product as prod

with open('lightson.in','w') as f:
    n = 100
    m = 9999
    print(n,m,file=f)
    for y in range(n):
        for x in range(n):
            print(1,y,x,y,file=f)
    for y in range(0,100):
        print(1,y,1,y + 1,file=f)
