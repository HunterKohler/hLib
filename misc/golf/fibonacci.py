# Try 1: 49 chars
i=0
j=1
for k in range(31):print(i);e=i+j;i=j;j=e

# Try 2: 45 chars
j=0
j=1
for k in range(32):print(i);i,j=j,i+j
