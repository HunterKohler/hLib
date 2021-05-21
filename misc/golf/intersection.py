# import sys
# for v in sys.argv[1:]:
#  x1,y1,w1,h1,x2,y2,w2,h2=map(int,v.split())
#  xl,xr=sorted([x1,x1+w1,x2,x2+w2])[1:3]
#  yl,yr=sorted([y1,y1+h1,y2,y2+h2])[1:3]
#  print((xr-xl)*(yr-yl))


import sys
# for v in sys.argv[1:]:
for v in ["87 59 23 49 55 36 38 35"]:
#  x1,y1,w1,h1,x2,y2,w2,h2=map(int,v.split())
 v=*map(int,v.split()),
 print(*v)
 ax1,ax2=sort(v[0],v[])
 ax1=v[0]
 ax2=ax1+v[2]
 ay1=v[1]
 ay2=ay1+v[3]
 bx1=v[4]
 bx2=bx1+v[6]
 by1=v[5]
 by2=ay1+v[7]
 print(ax1,ax2,ay1,ay2,bx1,bx2,by1,by2,)
#  xl,xr=sorted([x1,x1+w1,x2,x2+w2])[1:3]
#  yl,yr=sorted([y1,y1+h1,y2,y2+h2])[1:3]
#  print(((x2<=x1<=x2+w2 or x2<=x1+w1<=x2+w2) and (y2<=y1<=y2+h2 or y2<=y1+h1<=y2+h2)) * (xr-xl)*(yr-yl))

if bx1<=ax1<=bx2
