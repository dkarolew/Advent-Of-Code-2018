#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

std::vector<int> loadData(const std::string& fileName) {
    std::ifstream infile(fileName);
    std::vector<int> data;
    int x = 0;
    while (infile >> x) {
        data.push_back(x);
    }
    return data;
}

std::pair<int, int> sumMetadata(const std::vector<int>& data, int sum, int move) {
    int children = data[0 + move];
    int entries = data[1 + move];
    if(children == 0) {
        for(int i = 0; i < entries + 2; i++) {
            sum += data[i + move];
        }
        sum -= entries;
        return std::make_pair(sum, entries + move + 2);
    } else {
        for(int i = 0; i < children; i++) {
            std::vector<int> newData(data.begin() + move + 2, data.end());
            auto res = sumMetadata(newData, sum, 0);
            sum = res.first;
            move += res.second;
        }
        for(int i = move + 2; i < move + entries + 2; i++) {
            if(i < data.size()) {
                sum += data[i];
            }
        }
        return std::make_pair(sum, entries + move + 2);
    }
}
std::pair<int, int> getValueOfNode(const std::vector<int>& data, int move) {
    int children = data[0];
    int entries = data[1];
    std::vector<int> nodes;
    for(int i = 0; i < children; i++) {
        std::vector<int> newData(data.begin() + move + 2, data.end());
        auto res = getValueOfNode(newData, 0);
        move += res.second;
        nodes.push_back(res.first);
    }
    int sum = 0;
    if(children == 0) {
        return std::make_pair(sumMetadata(data, 0, move).first, entries + move + 2);
    } else {
        std::vector<int> indexes(data.begin() + 2 + move, data.begin() + entries + 2 + move);
        for(const auto i : indexes) {
            if(i <= nodes.size()) {
                sum += nodes[i - 1];
            }
        }
    }
    return std::make_pair(sum, move + entries + 2);
}


int main() {

    std::vector<int> data = loadData("input.txt");

    std::cout << "Part 1: " << sumMetadata(data, 0, 0).first << std::endl;

    std::cout << "Part 2 : " << getValueOfNode(data, 0).first << std::endl;

    return 0;
}