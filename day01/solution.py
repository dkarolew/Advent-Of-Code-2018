#!/usr/bin/env python3


def main():
    print('Part 1:', sum(map(int, filter(None, open('input.txt').read().split('\n')))))

    new_freq = 0
    current_freqs = set()
    isRepeated = False
    with open('input.txt') as f:
        content = f.readlines()
    lines = [line.strip() for line in content]

    while not isRepeated:
        for line in lines:
            current_freqs.add(new_freq)
            number = int("".join(line[1:]))
            if line[0] == '+':
                new_freq += number
            else:
                new_freq -= number
            if new_freq in current_freqs:
                print('Part 2:', new_freq)
                isRepeated = True
                break


if __name__ == '__main__':
    main()
