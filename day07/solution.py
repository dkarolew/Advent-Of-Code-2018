#!/usr/bin/env python3

import string


def load_data(filename):
    data = []
    file = open(filename, 'r')
    for line in file:
        data.append((line[5], line[36]))
    return data


def find_first_steps(data):
    res = []
    for c in string.ascii_uppercase:
        if c not in map(lambda item: item[1], data):
            res.append(c)
    return res


def get_neighbors(node, data):
    res = []
    for src, dest in data:
        if src == node:
            res.append(dest)
    return res


def get_parents(node, data):
    res = []
    for src, dest in data:
        if dest == node:
            res.append(src)
    return res


def create_graph(data):
    res = {}
    for c in string.ascii_uppercase:
        res[c] = get_neighbors(c, data)
    return res


def sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if ord(arr[j]) > ord(arr[j + 1]):
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


def dfs(G, vv, data):
    S = vv
    visited = []
    while S:
        v = S.pop(0)
        if v not in visited and all(e in visited for e in get_parents(v, data)) or v in find_first_steps(data):
            visited.append(v)
            for u in G[v]:
                S.append(u)
        S = sort(S)
    return visited


def convert(s):
    new = ""
    for x in s:
        new += x
    return new


def main():
    data = load_data('input.txt')
    print('Part 1:', convert(dfs(create_graph(data), find_first_steps(data), data)))

    available = find_first_steps(data)
    to_do = list(string.ascii_uppercase)
    workers = [[0, ''] for _ in range(5)]
    done = []
    curr_time = 0

    while to_do:
        for i, w in enumerate(workers):
            # worker have finished step
            if w[0] == 0 and not w[1] == '':
                done.append(w[1])
                if w[1] in to_do:
                    to_do.remove(w[1])
                workers[i][1] = ''
        for step in string.ascii_uppercase:
            # check which step is available and add those steps
            if step in done:
                done.remove(step)
                for v in get_neighbors(step, data):
                    if v not in available and all(e not in to_do for e in get_parents(v, data)):
                        available.append(v)

        for i, w in enumerate(workers):
            # take step
            if w[0] == 0 and w[1] == '':
                if available:
                    step = available.pop(0)
                    workers[i][0] = ord(step) - 4
                    workers[i][1] = step
        for i, w in enumerate(workers):
            # work on steps
            if w[0] > 0:
                workers[i][0] -= 1
        curr_time += 1

    print('Part 2:', curr_time - 1)


if __name__ == '__main__':
    main()
