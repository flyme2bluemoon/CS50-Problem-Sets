get_input = True
while get_input:
    try:
        credit = int(input("Number: "))
    except ValueError:
        pass
    else:
        if credit > 0:
            get_input = False

def checksum(card):
    reverse = card [::-1]
    sum = 0
    for i in range(1, len(reverse), 2):
        temp = str(int(reverse[i]) * 2)
        if (int(temp) < 10):
            sum += int(temp)
        else:
            sum += (int(temp[0]) + int(temp[1]))
    for i in range(0, len(reverse), 2):
        sum += int(reverse[i])
    if sum % 10 == 0:
        return True
    else:
        print("INVALID")
        return False

if (checksum(str(credit))):
    card = str(credit)
    if (card[0] == "3" and (card[1] in ["4", "7"])):
        print("AMEX")
    elif (card[0] == "5" and (card[1] in ["1", "2", "3", "4", "5"])):
        print("MASTERCARD")
    elif (card[0] == "4"):
        print("VISA")
    else:
        print("INVALID")