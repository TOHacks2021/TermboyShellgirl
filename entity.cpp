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

int Entity::getX() const {
    return x;
}

int Entity::getY() const {
    return y;
}

Player::Player(int x, int y, char color) : ColouredEntity(x, y, color) { }
void Player::draw() { }

ColouredEntity::ColouredEntity(int x, int y, char color) : Entity(x, y) { 
    this->color = color;
}
char ColouredEntity::getColor() const {
    return color;
}

Gem::Gem(int x, int y, char color) : ColouredEntity(x, y, color) { }
void Gem::draw() { }


PressurePlate::PressurePlate(int x, int y, char id) : Entity(x, y) { 
    this->id = id;
}
void PressurePlate::draw() { }
bool PressurePlate::getActive() const {
    return active;
}
char PressurePlate::getId() const {
    return id;
}
void PressurePlate::setActive(bool a) {
    active = a;
}


Switch::Switch(int x, int y, char id) : Entity(x, y) { 
    this->id = id;
}
void Switch::draw() { }
bool Switch::getActive() const {
    return active;
}
char Switch::getId() const {
    return id;
}
void Switch::setActive(bool a) {
    active = a;
}

Block::Block(int x, int y) : Entity(x, y) { }
void Block::draw() { }

Exit::Exit(int x, int y, char color) : ColouredEntity(x, y, color) { }
void Exit::draw() { }

Door::Door(int x, int y, char id, char type) : Entity(x, y) {
    this->id = id;
    this->type = type;
}
void Door::draw() { }

