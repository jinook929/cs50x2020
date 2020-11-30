import csv
import math
import sys

if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")

file = open(sys.argv[2], "r")
s = file.read()
match = False


def strCheck(str):
    counter = 0
    repeat = [0]
    for i in range(len(s) - (len(str)-1)):
        counter = 0
        if s[i:(i+len(str))] == str:
            for j in range(math.floor((len(s)-i)/len(str))):
                if s[i:(i+len(str))] == s[i+(len(str)*j):i+(len(str)*j)+len(str)]:
                    counter += 1
                else:
                    break
        repeat.append(counter)
    repeat.sort()
    counter = repeat[-1]
    return counter
    
    
if sys.argv[1] == "databases/small.csv":
    with open(sys.argv[1]) as cvsfile:
        csvreader = csv.reader(cvsfile, delimiter=',')
        for row in csvreader:
            if row[0] == "name":
                continue
            else:
                if int(row[1]) == strCheck("AGATC") and int(row[2]) == strCheck("AATG") and int(row[3]) == strCheck("TATC"):
                    match = True
                    print(row[0])
                    break
        if not match:
            print("No match")
elif sys.argv[1] == "databases/large.csv":
    with open(sys.argv[1]) as cvsfile:
        csvreader = csv.reader(cvsfile, delimiter=',')
        for row in csvreader:
            if row[0] == "name":
                continue
            else:
                if int(row[1]) == strCheck("AGATC") and int(row[2]) == strCheck("TTTTTTCT") and int(row[3]) == strCheck("AATG") and int(row[4]) == strCheck("TCTAG") and int(row[5]) == strCheck("GATA") and int(row[6]) == strCheck("TATC") and int(row[7]) == strCheck("GAAA") and int(row[8]) == strCheck("TCTG"):
                    match = True
                    print(row[0])
                    break
        if not match:
            print("No match")

file.close()
