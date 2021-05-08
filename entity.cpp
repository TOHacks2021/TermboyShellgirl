#include <iostream>
#include <string>
#include <vector>
#include "headers/entity.h"
using namespace std;

Entity::~Entity() {}
Entity::Entity(int x, int y) {
    this->x = x;
    this->y = y;
}