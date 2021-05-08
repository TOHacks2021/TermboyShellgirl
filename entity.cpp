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

class Player: public Entity {
    public:
        Player (int x, int y);
        void draw();
};

Player::Player(int x, int y) : Entity(x, y) { }

void Player::draw() { }



