# check command line arguments
# query database for all students in the house 
# print out each students full name and birth year
# sort alphabetically by last name then first name 
from cs50 import SQL
import csv
import sys



if len(sys.argv) !=2:
    sys.exit("error: please check command line arguments")

if sys.argv[1] not in["Gryffindor","Slytherin","Hufflepuff","Ravenclaw"]:
    sys.exit("Usage: python roster.py house")
   
wizhouse = sys.argv[1]
db = SQL("sqlite:///students.db")

rowDict = db.execute("select * from students where house=? order by last",wizhouse)


for row in rowDict:
    if row["middle"]==None:
        print(row["first"] +" "+ row["last"]+""+"," +" born" + " " + str(row["birth"]))
    else:
        print(row["first"]+ " "+row["middle"]+" "+row["last"]+ "" +", born" +" " + str(row["birth"]))