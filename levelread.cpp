#include "headers/levelread.h"
#include <iostream>
#include <string>
#include <vector>


Level::~Level() {}
void Level::draw() {}
Level::Level(int x, int y) {
    this->x = x;
    this->y = y;
}