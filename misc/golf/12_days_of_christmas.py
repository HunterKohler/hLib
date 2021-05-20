# Try 1: 546 chars
# arr=["A Partridge in a Pear Tree.","Two Turtle Doves, and","Three French Hens,","Four Calling Birds,","Five Gold Rings,","Six Geese-a-Laying,","Seven Swans-a-Swimming,","Eight Maids-a-Milking,","Nine Ladies Dancing,","Ten Lords-a-Leaping,","Eleven Pipers Piping,","Twelve Drummers Drumming,"]
# days=["First","Second","Third","Fourth","Fifth","Sixth","Seventh","Eighth","Ninth","Tenth","Eleventh","Twelfth"]
# for i in range(1,13):print(f"On the {days[i-1]} day of Christmas\nMy true love sent to me"),[print(arr[j]) for j in range(i)[::-1]],print()

# Try 2: 528 chars
for i in range(1,13):print(f'On the {["First","Second","Third","Fourth","Fifth","Sixth","Seventh","Eighth","Ninth","Tenth","Eleventh","Twelfth"][i-1]} day of Christmas\nMy true love sent to me'),[print(["A Partridge in a Pear Tree.","Two Turtle Doves, and","Three French Hens,","Four Calling Birds,","Five Gold Rings,","Six Geese-a-Laying,","Seven Swans-a-Swimming,","Eight Maids-a-Milking,","Nine Ladies Dancing,","Ten Lords-a-Leaping,","Eleven Pipers Piping,","Twelve Drummers Drumming,"][j]) for j in range(i)[::-1]],print()
