#!/usr/bin/env python3


# return initial state and pattern to process pots
def load_data(filename):
    file = open(filename, "r")
    patterns = []
    init_state = ''

    for line in file:
        if line[:13] == 'initial state':
            init_state = '...' + line.strip('\n').split(': ')[1] + 20 * '.'
        if len(line.strip('\n')) == 10:
            pattern = line.strip('\n').split(' => ')
            patterns.append((pattern[0], pattern[1]))
    file.close()

    return init_state, patterns


# evolute single pot to next generation
def pot_evolution(curr_state, patterns, pot_index):
    pots = ''.join(curr_state[pot_index - 2:pot_index + 3])
    for pattern in patterns:
        if pots == pattern[0]:
            if pattern[1] == '#':
                if pot_index == 2:
                    return pattern[1], True
            return pattern[1], False
    return '.', False


# return next state generation (each pot has been evoluted)
def next_generation(curr_state, patterns):
    next_gen = list(curr_state)
    extend = False
    for i in range(len(curr_state) - 2):
        next_gen[i + 2], extend = pot_evolution(curr_state, patterns, i + 2)
    if extend:
        next_gen = ['.'] + next_gen
    return ''.join(next_gen)


# return sum of plants starting from index '-3'
def sum_plants(curr_state):
    sum = 0
    for i, pot in enumerate(curr_state):
        if pot == "#":
            sum += i - 3

    return sum


def main():
    init_state, patterns = load_data("input.txt")

    # print('[0]:', init_state)
    state = init_state

    for i in range(20):
        state = next_generation(state, patterns)
        # print('[' + str(i + 1) + ']:', state)

    print('Part 1:', sum_plants(state))

    # equation is result of observation (after 100 generation, pots are moving forward once in each generation)
    print('Part 2:', (50000000000 - 100) * 62 + 5133 + 182 + 185 + 191)


if __name__ == "__main__":
    main()
