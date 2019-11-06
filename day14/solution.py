#!/usr/bin/env python3


# return input
def load_data(filename):
    file = open(filename, "r")
    data = 0
    for line in file:
        data = int(line)
    file.close()

    return data


# return tuple (digit of tens, digit of ones)
def get_digits(number):
    return (int(number / 10) % 10, number % 10) if number > 9 else [number]


# return beginning index of found sequence in given list
def find_sequence(seq, tab):
    return [i for i in range(len(tab)) if tab[i:i + len(seq)] == seq]


def part_1(number_of_recipes):
    e1 = 0  # recipe index of first elf
    e2 = 1  # recipe index of second elf
    recipes = [3, 7]

    while len(recipes) < number_of_recipes + 10:
        recipe = list(get_digits(recipes[e1] + recipes[e2]))
        recipes += recipe
        if e1 == (e1 + recipes[e1] + 1) % len(recipes) or e2 == (e2 + recipes[e2] + 1) % len(recipes):
            recipes += recipe
        e1 += recipes[e1] + 1
        e2 += recipes[e2] + 1
        e1 = e1 % len(recipes)
        e2 = e2 % len(recipes)

    return recipes


def part_2(sequence):
    e1 = 0  # recipe index of first elf
    e2 = 1  # recipe index of second elf
    offset = 0
    recipes = [3, 7]

    while True:
        recipe = list(get_digits(recipes[e1] + recipes[e2]))
        recipes += recipe
        if e1 == (e1 + recipes[e1] + 1) % len(recipes) or e2 == (e2 + recipes[e2] + 1) % len(recipes):
            recipes += recipe
        e1 += recipes[e1] + 1
        e2 += recipes[e2] + 1
        e1 = e1 % len(recipes)
        e2 = e2 % len(recipes)

        index = find_sequence(sequence, recipes[offset:])
        if index:
            return index[0] + offset
        else:
            offset += len(recipe)


def main():
    data = load_data("input.txt")
    sequence = [int(x) for x in str(data)]

    print('Part 1:', ''.join(map(str, part_1(data)[data:data + 10])))
    print('Part 2:', part_2(sequence))


if __name__ == "__main__":
    main()
