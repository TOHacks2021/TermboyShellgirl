#include <iostream>
#include <string>
#include <vector>
#include "headers/entity.h"
using namespace std;

class Player: public Entity {
    public:
        Player (int x, int y);
        void draw();
};

Player::Player(int x, int y) : Entity(int x, int y);

void Player::draw() {

}