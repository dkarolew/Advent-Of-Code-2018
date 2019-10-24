#include <iostream>
#include <fstream>
#include <vector>


// return serial number of grid
int loadData(const std::string& fileName) {
    std::ifstream infile(fileName);
    int x = 0;
    infile >> x;

    return x;
}

// return digit of hundreds
int hundredsDigit(int number) {
    std::string res = std::to_string(number);

    return res[res.length() - 3] - 48;

}

// create grid with fuel cells
std::vector<std::vector<int>> createGrid(int serialNumber) {
    std::vector<std::vector<int>> grid(300, std::vector<int>(300));
    for(int i = 0; i < 300; i++) {
        int rackID = (i + 1) + 10;
        for(int j = 0; j < 300; j++) {
            grid[i][j] = hundredsDigit(((rackID * (j + 1) + serialNumber) * rackID)) - 5;
        }
    }
    return grid;
}

// get total fuel power of square with specified size
int sumSquare(const std::vector<std::vector<int>>& grid, int x, int y, int squareSize) {
    int sum = 0;
    for(int i = x; i < x + squareSize; i ++) {
        for(int j = y; j < y + squareSize; j ++) {
            sum += grid[i][j];
        }
    }
    return sum;
}

// return (x, y) of point which is top-left corner of any size square with max fuel
std::pair<std::pair<int, int>, int> maxSquare(const std::vector<std::vector<int>>& grid,
                                                const std::vector<int>& squareSizes) {
    std::pair<std::pair<int, int>, int> max_point;
    auto curr_sum = INT64_MIN;
    for(const auto squareSize : squareSizes) {
        for (int i = 0; i < grid.size() - squareSize; i++) {
            for (int j = 0; j < grid[0].size() - squareSize; j++) {
                if (sumSquare(grid, i, j, squareSize) > curr_sum) {
                    curr_sum = sumSquare(grid, i, j, squareSize);
                    max_point = {{i + 1, j + 1}, squareSize};
                }
            }
        }
    }
    return max_point;
}


int main() {

    int data = loadData("input.txt");

    auto grid = createGrid(data);
    std::vector<int> squareSizes{3};
    auto point = maxSquare(grid, squareSizes);

    std::cout << "Part 1: (" << point.first.first << ", " << point.first.second << ")" << std::endl;


    std::vector<int> squareSizes2;
    for(int i = 1; i <= grid.size(); i++) {
        squareSizes2.push_back(i);
    }
    auto point2 = maxSquare(grid, squareSizes2);

    std::cout << "Part 2: (" << point2.first.first << ", " << point2.first.second << "), " <<
    point2.second << std::endl;

    return 0;
}