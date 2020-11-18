get_input = True
while get_input:
    try:
        change = float(input("Change owed: "))
    except ValueError:
        pass
    else:
        if change > 0:
            get_input = False

counter = 0

change *= 100

quarter = True
while quarter:
    if change >= 25:
        change -= 25
        counter += 1
    else:
        quarter = False

dime = True
while dime:
    if change >= 10:
        change -= 10
        counter += 1
    else:
        dime = False

nickel = True
while nickel:
    if change >= 5:
        change -= 5
        counter += 1
    else:
        nickel = False

penny = True
while penny:
    if change >= 1:
        change -= 1
        counter += 1
    else:
        penny = False

print(counter)