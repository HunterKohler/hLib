import sys
for i in sys.argv:len({x for x in i.lower()if 96<ord(x)<123})==26and print(i)
