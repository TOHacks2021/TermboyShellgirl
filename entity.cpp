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

Player::Player(int x, int y, char color) : Entity(x, y) { 
    this->color = color;
}
void Player::draw() { }

Gem::Gem(int x, int y, char color) : Entity(x, y) { 
    this->color = color;
}
void Gem::draw() { }


PressurePlate::PressurePlate(int x, int y, char id) : Entity(x, y) { 
    this->id = id;
}
void PressurePlate::draw() { }

Switch::Switch(int x, int y, char id) : Entity(x, y) { 
    this->id = id;
}
void Switch::draw() { }
