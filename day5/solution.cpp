#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

std::string readFile(std::string fileName){
    std::ifstream file(fileName);
    std::string data;
    if (file.is_open()) {
        while (getline(file, data)) {
        }
        file.close();
    }
    return data;
}

std::string reactPolymer(std::string polymer) {
    for (unsigned int i = 0; i < polymer.size(); i++) {
        if (polymer[i] != polymer[i + 1] && std::tolower(polymer[i]) == std::tolower(polymer[i + 1])) {
            polymer.erase(i, 2);
            i = 0;
        }
    }
    return polymer;
}

std::string removeUnit(std::string polymer, char unit) {
    for (unsigned int i = 0; i < polymer.size(); i++) {
        if(std::tolower(polymer[i]) == unit) {
            polymer.erase(i, 1);
            i = 0;
        }
    }
    return polymer;
}

bool compare(std::pair<char ,int> i, std::pair<char, int> j) {
    return i.second < j.second;
}

int main() {

    std::string polymer = readFile("input.txt");
    polymer = reactPolymer(polymer);
    std::cout << "Part 1: " << polymer.size() << std::endl;

    polymer = reactPolymer(polymer);
    std::string units = "abcdefghijklmnopqrstuvwxyz";
    std::map<char, int> polymer_lengths;
    std::string temp;
    for(char unit : units) {
        temp = polymer;
        polymer_lengths[unit] = reactPolymer(removeUnit(temp, unit)).size();
    }
    std::pair<char, int> min = *min_element(polymer_lengths.begin(), polymer_lengths.end(), compare);
    std::cout << "Part 2: " << min.second << std::endl;

    return 0;
}
