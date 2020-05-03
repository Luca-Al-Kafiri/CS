import csv
from sys import argv


f = open(argv[1], "r")
data = csv.DictReader(f)
strs = data.fieldnames
d = open(argv[2], "r")
dna = d.read()

counter = []

for i in range(1, len(strs)):
    count = 0
    n = 1

    while strs[i]*n in dna:
        n += 1
    if (n - 1) > count:
        count = n - 1
    counter.append(count)

for row in data:
    x = 0
    match = False
    for c in range(len(strs) - 1):
        if int(row[strs[c+1]]) == int(counter[c]):
            x += 1
    if x == len(strs) - 1:
        print(row[strs[0]])
        match = True
        break
if match == False:
    print("No match")
f.close()
d.close()
