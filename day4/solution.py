#!/usr/bin/env python3

from datetime import datetime
import numpy as np

fmt = '%Y-%m-%d %H:%M'


def get_records(data):
    records = []
    file = open(data, 'r')
    for line in file:
        date = line[1:17]
        info = line[19:].rstrip()
        records.append((date, info))
    records.sort(key=lambda record: datetime.strptime(record[0], fmt))
    return records


def get_sleepyhead_id(records):
    guards = {}
    napes = []
    for record in records:
        if record[1][:7] == 'Guard #':
            if napes:
                if not guards.get(id_guard):
                    guards.update({id_guard: sum(napes)})
                else:
                    guards.update({id_guard: guards.get(id_guard) + sum(napes)})
                napes.clear()
            id_guard = record[1].split()[1].strip('#')
        if record[1] == 'falls asleep':
            d1 = datetime.strptime(record[0], fmt)
        if record[1] == 'wakes up':
            d2 = datetime.strptime(record[0], fmt)
            napes.append(int((d2 - d1).seconds / 60))
    return max(guards, key=guards.get)


def get_most_asleep_minute(records, id_guard):
    minutes = 60 * [0]
    i = 0
    flag = False
    start_sleep = []
    end_sleep = []
    for record in records:
        if record[1] == 'Guard #' + id_guard + ' begins shift' and not flag:
            start_sleep.append(i + 1)
            flag = True
        elif record[1][:7] == 'Guard #' and flag:
            end_sleep.append(i - 1)
            flag = False
        i += 1
    indexes = []
    k = 0
    for i in range(len(start_sleep)):
        indexes.append(np.arange(start_sleep[i], end_sleep[i] + 1))
    for index in indexes:
        for i in index:
            if not k % 2:
                t1 = int(records[i][0][14:])
            else:
                t2 = int(records[i][0][14:])
                nap_minutes = np.arange(t1, t2)
                for j in range(len(minutes)):
                    if j in nap_minutes:
                        minutes[j] += 1
            k += 1
        k = 0
    return minutes.index(max(minutes)), max(minutes)


def main():
    records = get_records('input.txt')
    sleepyhead_id = get_sleepyhead_id(records)
    minute, _ = get_most_asleep_minute(records, sleepyhead_id)
    print('Part 1:', int(sleepyhead_id) * minute)

    guards = {}
    for record in records:
        if record[1][:7] == 'Guard #':
            id_guard = record[1].split()[1].strip('#')
            guards[id_guard] = 0
    del guards['1553']
    del guards['283']
    max_count = 0
    max_id = 0
    max_minute = 0
    for id_guard in guards.keys():
        guards[id_guard], _ = get_most_asleep_minute(records, id_guard)
        minute, count = get_most_asleep_minute(records, id_guard)
        if count > max_count:
            max_count = count
            max_id = id_guard
            max_minute = minute
    print('Part 2:', int(max_id) * max_minute)


if __name__ == '__main__':
    main()
