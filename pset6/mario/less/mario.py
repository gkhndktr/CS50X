while True:
    height = input("Height:")
    if height.isnumeric():
        height = int(height)
        if 1 <= height and height <=8:
            break
        else:True
    else:
        True
for line in range(height):
    for x in range(height - line -1):
        print(" ",end="")
    for y in range(line +1):
        print("#",end="")
    print()