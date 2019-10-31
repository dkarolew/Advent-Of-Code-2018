#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Cart{
    int x;
    int y;
    char dir; // direction
    int id;
    char turn = 'L'; // last turn on intersection
    inline bool operator!=(const Cart& cart) const { return this->id != cart.id; }
};

std::vector<std::vector<char>> loadData(const std::string& fileName) {
    std::ifstream file(fileName);
    std::vector<std::vector<char>> data;
    std::string line;
    while(getline(file, line)) {
        data.emplace_back();
        for (char i : line) {
            data.back().push_back(i);
        }
    }
    return data;
}

std::vector<Cart> getCarts(std::vector<std::vector<char>>& track) {
    std::vector<Cart> carts;
    int id = 1;
    for(int i = 0; i < track.size(); i++) {
        for(int j = 0; j < track[i].size(); j++) {
            if(track[i][j] == '>') {
                track[i][j] = '-';
                carts.push_back({i, j, '>', id});
                id++;
            }
            if(track[i][j] == '<') {
                track[i][j] = '-';
                carts.push_back({i, j, '<', id});
                id++;
            }
            if(track[i][j] == 'v') {
                track[i][j] = '|';
                carts.push_back({i, j, 'v', id});
                id++;
            }
            if(track[i][j] == '^') {
                track[i][j] = '|';
                carts.push_back({i, j, '^', id});
                id++;
            }
        }
    }
    return carts;
}

void cross(char& dir, char& turn) {
    switch(turn) {
        case 'L':
            turn = 'S';
            if(dir == 'v') {
                dir = '>';
                break;
            }
            if(dir == '^') {
                dir = '<';
                break;
            }
            if(dir == '>') {
                dir = '^';
                break;
            }
            if(dir == '<') {
                dir = 'v';
                break;
            }
            break;
        case 'S':
            turn = 'R';
            break;
        case 'R':
            turn = 'L';
            if(dir == 'v') {
                dir = '<';
                break;
            }
            if(dir == '^') {
                dir = '>';
                break;
            }
            if(dir == '>') {
                dir = 'v';
                break;
            }
            if(dir == '<') {
                dir = '^';
                break;
            }
            break;
        default:
            break;
    }
}

void move(Cart& cart, const std::vector<std::vector<char>>& track) {
    int x = cart.x;
    int y = cart.y;
    switch(cart.dir) {
        case '>':
            cart.y += 1;
            if(track[x][y + 1] == '\\') cart.dir = 'v';
            if(track[x][y + 1] == '/') cart.dir = '^';
            if(track[x][y + 1] == '+') cross(cart.dir, cart.turn);
            break;
        case '<':
            cart.y -= 1;
            if(track[x][y - 1] == '/') cart.dir = 'v';
            if(track[x][y - 1] == '\\') cart.dir = '^';
            if(track[x][y - 1] == '+') cross(cart.dir, cart.turn);
            break;
        case 'v':
            cart.x += 1;
            if(track[x + 1][y] == '/') cart.dir = '<';
            if(track[x + 1][y] == '\\') cart.dir = '>';
            if(track[x + 1][y] == '+') cross(cart.dir, cart.turn);
            break;
        case '^':
            cart.x -= 1;
            if(track[x - 1][y] == '\\') cart.dir = '<';
            if(track[x - 1][y] == '/') cart.dir = '>';
            if(track[x - 1][y] == '+') cross(cart.dir, cart.turn);
            break;
        default:
            break;
    }
}

bool checkCollision(const Cart& c, const std::vector<Cart>& carts) {
    for(const auto& cart : carts) {
        if(c != cart) {
            if (c.x == cart.x && c.y == cart.y) return true;
        }
    }
    return false;
}

int main() {

    auto track = loadData("input.txt");
    auto carts = getCarts(track);

    bool collision = false;
    while(!collision) {
        std::sort(carts.begin(), carts.end(), [](Cart c1, Cart c2) { return c1.x == c2.x ? c1.y < c2.y : c1.x < c2.x; });
        for(auto& cart : carts) {
            move(cart, track);
            if (checkCollision(cart, carts)) {
                std::cout << "Part 1: " << cart.y << ", " << cart.x << std::endl;
                collision = true;
                break;
            }
        }
    }

    track = loadData("input.txt");
    carts = getCarts(track);
    while(carts.size() != 1) {
        std::sort(carts.begin(), carts.end(), [](Cart c1, Cart c2) { return c1.x == c2.x ? c1.y < c2.y : c1.x < c2.x; });
        for(int i = 0; i < carts.size(); i++) {
            move(carts[i], track);
            if (checkCollision(carts[i], carts)) {
                carts.erase(std::remove_if(carts.begin(), carts.end(), [&](const Cart & c) {
                    return c.x == carts[i].x && c.y == carts[i].y; }), carts.end());
                i = 0;
            }
        }
    }
    std::cout << "Part 2: " << carts[0].y << ", " << carts[0].x << std::endl;

    return 0;
}