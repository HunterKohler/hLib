import json
from string import ascii_uppercase

def read(*files):
    return "".join(open(file).read() for file in files).replace(" ","")

length = 6
found = read("found1","found2")
krypton = read("krypton5")

def chunk(s):
    return " ".join(s[i * 5:min(i * 5 + 5,len(s))] for i in range(int(len(s) / 5)+1))


english = json.load(open("../english.json"))["monogram"]
english = "".join(sorted(english.keys(),key=lambda k: -english[k]))

parts = ["".join(found[i + 6*j] for j in range(int(len(found) / 6))) for i in range(6)]
parts = [{k:p.count(k) for k in ascii_uppercase} for p in parts]
parts = ["".join(sorted(p.keys(),key=lambda k: -p[k])) for p in parts]

def dist(a,b):
    a = ord(a)
    b = ord(b)
    if b < a:
        b += 26
    return b - a

def avg_dist(a,b):
    return int(sum(dist(i,j) for i,j in zip(a,b)) / len(a))


key = "".join(chr(ord("A") + avg_dist(p,english)) for p in parts)

print(english)
print(key)

def apply(s,key):
    for i in range(len(s)):
        s[i] = dist(s[i],dist())
    return s
