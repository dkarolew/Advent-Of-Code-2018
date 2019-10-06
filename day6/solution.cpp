#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>


std::vector<std::pair<int, int>> getCoordinates(std::string fileName) {
    std::ifstream file(fileName);
    std::string line;
    std::string delimiter = ", ";
    std::size_t pos;
    int x,y;
    std::vector<std::pair<int, int>> coordinates;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            pos = line.find(delimiter);
            x = std::stoi(line.substr(0, pos));
            y = std::stoi(line.substr(pos + delimiter.length(), line.length()));
            auto pair = std::make_pair(x, y);
            coordinates.push_back(pair);
        }
        file.close();
    }
    return coordinates;
}

bool comparePairByFirst(const std::pair<int, int>& i, const std::pair<int, int>& j) {
    return i.first < j.first;
}

bool comparePairBySecond(const std::pair<int, int>& i, const std::pair<int, int>& j) {
    return i.second < j.second;
}

int Manhattan(const std::pair<int, int>& x, const std::pair<int, int>& y) {
    return abs(x.first - y.first) + abs(x.second - y.second);
}

std::vector<std::pair<int, int>> getBounds(const std::vector<std::pair<int, int>>& coordinates) {
    std::vector<std::pair<int,int>> bounds;
    
    auto p1 = *std::min_element(coordinates.cbegin(), coordinates.cend(), comparePairByFirst);
    auto p2 = *std::min_element(coordinates.cbegin(), coordinates.cend(), comparePairBySecond);
    auto p3 = *std::max_element(coordinates.cbegin(), coordinates.cend(), comparePairByFirst);
    auto p4 = *std::max_element(coordinates.cbegin(), coordinates.cend(), comparePairBySecond);

    bounds.push_back(p1);
    bounds.push_back(p2);
    bounds.push_back(p3);
    bounds.push_back(p4);

    return bounds;
    }

std::pair<int, int> getClosestPoint(const std::pair<int, int>& p1, const std::vector<std::pair<int, int>>& coordinates) {
    std::pair<int, int> closest_point = coordinates[0];
    int min = INT32_MAX;

    for(const auto& p2 : coordinates) {
        int dist = Manhattan(p1, p2);
        if(dist < min) {
            min = dist;
            closest_point = p2;
        }
    }
    return closest_point;
}

std::set<std::pair<int, int>> getInfinitePoints(const std::vector<std::pair<int, int>>& coordinates) {
    std::set<std::pair<int, int>> infinitePoints;
    std::vector<std::pair<int, int>> bounds = getBounds(coordinates);

    for(int x = bounds[0].first; x <= bounds[2].first; x++) {
         infinitePoints.insert(getClosestPoint({x, bounds[1].second}, coordinates));
         infinitePoints.insert(getClosestPoint({x, bounds[3].second}, coordinates));
    }
    for(int y = bounds[1].second; y <= bounds[3].second; y++) {
         infinitePoints.insert(getClosestPoint({bounds[0].first, y}, coordinates));
         infinitePoints.insert(getClosestPoint({bounds[2].first, y}, coordinates));
    }
    return infinitePoints;
}

int main() {

    std::vector<std::pair<int, int>> coordinates = getCoordinates("input.txt");
    std::vector<std::pair<int, int>> bounds = getBounds(coordinates);
    std::set<std::pair<int, int>> infinitePoints = getInfinitePoints(coordinates);
    std::map<std::pair<int,int>, int> fields;

    for(int i = bounds[0].first; i < bounds[2].first;  i++){
        for(int j = bounds[1].second; j < bounds[3].second; j++){
            std::pair<int, int> closest_point = getClosestPoint({i, j}, coordinates);
            if(infinitePoints.find(closest_point) == infinitePoints.end())
                fields[closest_point]++;
        }
    }
    int max = 0;
    for(auto p : fields){
        if(p.second > max)
            max = p.second;
    }
    std::cout << "Part 1: " << max << std::endl;

    int area = 0;
    int sum;
    for(int i = bounds[0].first; i < bounds[2].first;  i++){
        for(int j = bounds[1].second; j < bounds[3].second; j++) {
            sum = 0;
            for(const auto& p : coordinates) {
                sum += Manhattan(p, {i, j});
            }
            if(sum < 10000) area++;
        }
    }
    std::cout << "Part 2: " << area << std::endl;

    return 0;
}
