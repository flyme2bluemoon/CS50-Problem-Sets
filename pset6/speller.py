the_words = set()

def check(word):
    if word.lower() in the_words:
        return True
    else:
        return False

def load(dictionary):
    the_dictionary = open(dictionary, "r")
    for line in the_dictionary:
        the_words.add(line.rstrip("\n"))
    the_dictionary.close()
    return True

def size():
    return len(words)

def unload():
    return True