#include "headers/levelread.h"
#include <iostream>
#include <string>
#include <vector>


Level::~Level() {}
void Level::draw() {}
Level::Level(string filename) {
    parseFile(filename);
}

void Level::parseFile(string filename) {
    ifstream file(filename);
    vector<string> lines;
    string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }
}