#include <iostream>
#include <string>
#include <vector>

#include "headers/entity.h"

Entity::~Entity() {}
void Entity::draw(WINDOW* win) {}
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
void Player::draw(WINDOW* win) { }

ColouredEntity::ColouredEntity(int x, int y, char color) : Entity(x, y) { 
    this->color = color;
}
char ColouredEntity::getColor() const {
    return color;
}

Gem::Gem(int x, int y, char color) : ColouredEntity(x, y, color) { }

void
Gem::draw(WINDOW* win)
{
	mvwprintw(win, this->y, this->x, "$");
}

PressurePlate::PressurePlate(int x, int y, char id) : Entity(x, y) { 
    this->id = id;
}
void PressurePlate::draw(WINDOW* win) { }
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
void Switch::draw(WINDOW* win) { }
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
void Block::draw(WINDOW* win) { }

Exit::Exit(int x, int y, char color) : ColouredEntity(x, y, color) { }
void Exit::draw(WINDOW* win) { }

Door::Door(int x, int y, char id, char type) : Entity(x, y) {
    this->id = id;
    this->type = type;
}
void Door::draw(WINDOW* win) { }

