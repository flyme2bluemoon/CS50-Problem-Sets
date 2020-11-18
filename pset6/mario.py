get_input = True
while get_input:
    try:
        height = int(input("Height: "))
    except ValueError:
        pass
    else:
        if height > 0 and height <= 8:
            get_input = False

space = height - 1
pound = 1
for i in range(height):
    print(" " * space + "#" * pound + "  " + "#" * pound)
    space -= 1
    pound += 1