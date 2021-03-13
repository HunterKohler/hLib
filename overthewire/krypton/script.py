from matplotlib import pyplot as plt
from string import ascii_uppercase
from pprint import pprint
from itertools import product

monographs = ["E","T","A","O","I","N","S","R","H","D","L","U","C","M","F","Y","W","G","P","B","V","K","X","Q","J","Z"]
digraphs = ["TH","ER","ON","AN","RE","HE","IN","ED","ND","HA","AT","EN","ES","OF","OR","NT","EA","TI","TO","IT","ST","IO","LE","IS","OU","AR","AS","DE","RT","VE"]
trigraphs =["THE","AND","THA","ENT","ION","TIO","FOR","NDE","HAS","NCE","EDT","TIS","OFT","STH","MEN"]
# doubles = ["SS","EE","TT","FF","LL","MM","OO"]

def read(*files):
    return "".join(open(file) for file in files).replace(" ","")

message = read("found1","found2","found3")
password = read("krypton")

freq = [
    {k:message.count(k)/len(message) for k in ascii_uppercase},
    {k:message.count(k)/(len(message)-1) for k in product(ascii_uppercase,repeat=2)},
    {k:message.count(k)/(len(message)-2) for k in product(ascii_uppercase,repeat=3)}
]
