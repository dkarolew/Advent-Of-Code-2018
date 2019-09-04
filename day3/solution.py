#!/usr/bin/env python3


class Rectangle:
    def __init__(self, offset_x, offset_y, width, height):
        self.width = width
        self.height = height
        self.offset_x = offset_x
        self.offset_y = offset_y


# return fabric rectangles (claim)
def parse_data(data):
    claims = []
    f = open(data, 'r')
    i = 1
    for line in f:
        rect = line.strip('#' + str(i)).strip(' @').split(':')
        offset_x, offset_y = map(int, rect[0].split(','))
        width, height = map(int, rect[1].split('x'))
        claims.append(Rectangle(offset_x, offset_y, width, height))
        i = i + 1
    return claims


def create_surface(rectangles):
    surface = {}
    for rect in rectangles:
        for x in range(rect.width):
            for y in range(rect.height):
                pos_x, pos_y = rect.offset_x + x, rect.offset_y + y
                if (pos_x, pos_y) not in surface:
                    surface[(pos_x, pos_y)] = 1
                else:
                    surface[(pos_x, pos_y)] += 1
    return surface


def overlap(surface, rect):
    for x in range(rect.width):
        for y in range(rect.height):
            pos_x, pos_y = rect.offset_x + x, rect.offset_y + y
            if surface[(pos_x, pos_y)] > 1:
                return True
    return False


def main():
    claims = parse_data('input.txt')
    surface = create_surface(claims)
    inches = sum([i > 1 for i in surface.values()])
    print('Part 1:', inches)

    id_claim = 1
    for claim in claims:
        if not overlap(surface, claim):
            print('Part 2:', id_claim)
            break
        id_claim = id_claim + 1


if __name__ == '__main__':
    main()
