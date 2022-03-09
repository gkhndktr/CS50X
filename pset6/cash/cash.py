from cs50 import get_float
penny = 0
nickel = 0
dime = 0
quarter = 0
while True:
    owed = get_float("Owed $: ")
    if owed < 0:
        continue
    else:
        owed = round(owed * 100);
        break
    
while owed > 0:
    while quarter + 25 <= owed:
        # //calculates if quarter should be increased or calculate with lower money variables
        quarter = quarter + 25 
    owed = owed - quarter
    while dime + 10 <= owed:
        # //calculates if dime should be increased or calculate with lower money variables
        dime = dime + 10
    owed = owed - dime
    while nickel + 5 <= owed:
        # //calculates if nickel should be increased or calculate with lower money variables
        nickel = nickel + 5
    owed = owed - nickel
    penny = owed 
    # //in any case owed is smaller than 5 now and pennies can be used.
    owed = owed - penny
Penny_given = penny
nickel_given = nickel / 5
dime_given = dime / 10 
quarter_given = quarter / 25
# //above total values are divided by their money values. so quantity given is calculated.
result = Penny_given + nickel_given + dime_given + quarter_given
result = int(result)
print(f"{result}")
    


