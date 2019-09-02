#!/usr/bin/env python3


def read_file(filename: str):
    with open(filename) as f:
        content = f.readlines()
    return [line.strip() for line in content]


# return the index of a letter that is different
def strings_differ_one_letter(str1, str2):
    differences = 0
    index = 0
    for i in range(len(str1)):
        if not str1[i] == str2[i]:
            differences += 1
            index = i
    return index if differences == 1 else -1


def main():
    twos_counter = 0
    threes_counter = 0
    storage = {}
    for id in lines:
        for letter in id:
            if letter in storage:
                storage[letter] += 1
            else:
                storage[letter] = 1
        if 2 in storage.values():
            twos_counter += 1
        if 3 in storage.values():
            threes_counter += 1
        storage.clear()
    print('Part 1:', twos_counter * threes_counter)

    for id1 in lines:
        for id2 in lines:
            index = strings_differ_one_letter(id1, id2)
            if index != -1:
                print('Part 2:', id1[:index] + id1[index + 1:])
                return


if __name__ == '__main__':
    lines = read_file('input.txt')
    main()
