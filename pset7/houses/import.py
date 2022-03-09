# check command line arguments
# open csv file given by command line argument
# for each row, parse name 
# insert each student into the students table of students.db


# use csv reader
# use split on strings to split into words
# use none for students middle name if they dont have one 
# use db.execute to insert a row into table.

from cs50 import SQL
import csv
import sys

if len(sys.argv) !=2:
    sys.exit("error: please check command line arguments")
if not (sys.argv[1].endswith(".csv")):
    sys.exit("error: wrong file type. csv file type must be submitted")
                
db = SQL("sqlite:///students.db")


with open(sys.argv[1]) as file:
    reader=csv.DictReader(file)
    for row in reader:
        namely = row["name"].split()
        if len(namely)== 2:
            first = namely[0]
            middle= None
            last= namely[1]
        else:
            first = namely[0]
            middle=namely[1]
            last= namely[2]
        db.execute ("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)",first, middle, last, row["house"], row["birth"])
