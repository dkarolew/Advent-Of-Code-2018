#!/usr/bin/env python3


def main():
    print(sum(map(int, filter(None, open('input.txt').read().split('\n')))))

    result = 0
    current_values = set()
    is_repeating = False
    with open('input.txt') as f:
        content = f.readlines()
    lines = [line.strip() for line in content]

    while not is_repeating:
        for line in lines:
            current_values.add(result)
            number = int("".join(line[1:]))
            if line[0] == '+':
                result += number
            else:
                result -= number
            if result in current_values:
                print(result)
                is_repeating = True
                break


if __name__ == '__main__':
    main()
