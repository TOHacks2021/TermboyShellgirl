#include <iostream>
#include <string>
#include <vector>

#include "headers/entity.h"

Entity::~Entity() {}
void Entity::draw() {}
Entity::Entity(int x, int y) {
    this->x = x;
    this->y = y;
}

