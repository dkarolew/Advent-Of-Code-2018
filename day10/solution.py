#!/usr/bin/env python3

import math


def load_data(filename):
    file = open(filename, "r")
    points = []

    for line in file:
        pos = line[10:24].split(",")
        vel = line[36:42].split(",")
        point = {'pos': [int(pos[0]), int(pos[1])], 'vel': [int(vel[0]), int(vel[1])]}
        points.append(point)
    file.close()

    return points


def bounds(points):
    x = list(map(lambda p: p['pos'][0], points))
    y = list(map(lambda p: p['pos'][1], points))

    return min(x), min(y), max(x) - min(x) + 1, max(y) - min(y) + 1


def move(points):
    for i, point in enumerate(points):
        points[i]['pos'][0] += point['vel'][0]
        points[i]['pos'][1] += point['vel'][1]


def visualise(points, bb):
    for x in range(bb[3]):
        for y in range(bb[2]):
            if (y + bb[0], x + bb[1]) in [tuple(point['pos']) for point in points]:
                print('#', end='')
            else:
                print('.', end='')
        print()
    print()


def main():
    time = 0
    points = load_data("input.txt")
    height = math.inf

    print("Part 1:", "\n")

    while True:
        time += 1
        move(points)
        bb = bounds(points)

        if bb[3] <= 25:
            visualise(points, bb)
        if height < bb[3]:
            break
        height = bb[3]

    print("Part 2:", time - 1)


if __name__ == '__main__':
    main()
