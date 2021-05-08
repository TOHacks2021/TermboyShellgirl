#include "headers/levelread.h"

using namespace std;

Level::~Level() { }
void Level::draw() { }
Level::Level(string filename) {
    parseFile(filename);
}

void Level::parseFile(string filename) {
    /* ifstream file(filename); */
    /* vector<string> lines; */
    /* string line; */

    /* while (getline(file, line)) { */
    /*     lines.push_back(line); */
    /* } */
}
