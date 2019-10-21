#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>


std::pair<int, int> loadData(const std::string& fileName) {
    std::ifstream infile(fileName);
    std::string line;
    std::getline(infile, line);
    std::vector<std::string> tokens;
    size_t pos = 0;
    while ((pos = line.find(' ')) != std::string::npos) {
        tokens.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    return {std::stoi(tokens[0]), std::stoi(tokens[6])};
}

std::list<int>::iterator rotateClockwise(std::list<int>::iterator begin,
        std::list<int>::iterator end, std::list<int>::iterator curr) {
    return std::next(curr, 1) == end ? begin : std::next(curr, 1);
}

std::list<int>::iterator rotateCounterClockwise(std::list<int>::iterator begin,
        std::list<int>::iterator end, std::list<int>::iterator curr) {
    return curr == begin ? std::next(end, -1) : std::next(curr, -1);
}

size_t highestScore(int turn, int lastMarble) {
    std::list<int> circle;
    std::vector<size_t> players(turn, 0);
    circle.push_front(0);
    auto it = circle.begin();
    int counter = 0;

    for(int i = 1; i <= lastMarble; i++) {
        if(i % 23) {
             it = circle.insert(rotateClockwise(circle.begin(), circle.end(),
                                               rotateClockwise(circle.begin(), circle.end(), it)), i);
        } else {
            for(int j = 0; j < 7; j++) {
                it = rotateCounterClockwise(circle.begin(), circle.end(), it);
            }
            players[counter] += *it + i;
            it = circle.erase(it);
        }
        counter++;
        if(counter == turn) {
            counter = 0;
        }
    }
    return *std::max_element(std::begin(players), std::end(players));
}


int main() {

    auto data = loadData("input.txt");
    int players = data.first;
    int lastMarble = data.second;

    std::cout << "Part 1: " << highestScore(players, lastMarble) << std::endl;

    std::cout << "Part 2: " << highestScore(players, 100*lastMarble) << std::endl;

    return 0;
}

