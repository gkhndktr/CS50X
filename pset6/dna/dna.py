import csv
import sys
import re

with open(sys.argv[1]) as database:
    with open(sys.argv[2]) as sample:
        strPointer = database.readline().rstrip("\n").split(",")[1:]
        # filters str names from the top row
        sampler= sample.read()
        # reads sample file
        personTables=database.readlines()
        # filters names and str values, exludes str names
        strDict={}
        for i in strPointer:
            res = max(re.findall('((?:' + re.escape(i) + ')*)', sampler), key = len)
            neededNumbers = int(len(res)/len(i))
            strDict[i]=neededNumbers
        # counts max occurence of the str names in the sample file.
        strLookup= str(list((strDict.values()))).lstrip("[").rstrip("]").replace(", ",",")
        # max consecutive str number
        database.seek(0)
        # restarts cursor position, so file can be scanned from the beginning
        if strLookup not in database.read():
            print("No match")
        else:
            for i in personTables:
                if strLookup in i:
                    print(i.split(",")[0])
                    break