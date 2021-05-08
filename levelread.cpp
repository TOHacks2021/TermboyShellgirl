#include "headers/levelread.h"
#include <fstream>
#include <string>
#include <vector>
#include "headers/config.h"

Level::~Level() {}
Level::Level(std::string filename) {
    parseFile(filename);
}

void Level::draw() {}


void Level::parseFile(std::string filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    length = lines.at(0).length();
    height = lines.size();
    grid = new char*[length];

    for (int i = 0; i < length; i++) {
        grid[i] = new char[height];
    }

    const std::string letters = "abcdefhijkmnopqrstuvwxyz";

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < height; j++) {
            if (lines.at(j).at(i) == '#' || letters.find((lines.at(j).at(i)) 
            != std::string::npos)) {
                grid[i][j] = tiles.wall;
            }
            else {
                grid[i][j] = tiles.empty;
            }
        }
    }
}