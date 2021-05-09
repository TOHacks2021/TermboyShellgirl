#include <iostream>
#include <string>
#include <vector>

#include "headers/render.h"
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
	int hlcolor = COLOR_PAIR((ColouredEntity::RED == this->getColor()) ?  term_red : term_blue);
	wattron(win, hlcolor);
	mvwprintw(win, this->y, this->x, "$");
	wattroff(win, hlcolor);
}

PressurePlate::PressurePlate(int x, int y, char id) : Entity(x, y) { 
    this->id = id;
}

void
PressurePlate::draw(WINDOW* win)
{ 
	mvwprintw(win, this->y, this->x, "=");
}
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

void
Switch::draw(WINDOW* win)
{
	mvwprintw(win, this->y, this->x, this->getActive() ? "\\" : "/");
}

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

void
Block::draw(WINDOW* win)
{
	mvwprintw(win, this->y, this->x, "@");
}

Exit::Exit(int x, int y, char color) : ColouredEntity(x, y, color) { }

void
Exit::draw(WINDOW* win)
{
	char* door_char = "";

	switch (this->getColor()) {
		case ColouredEntity::RED:
			door_char = "]";
			break;
		case ColouredEntity::BLUE:
			door_char = "[";
			break;
	}
	/* careful not to print off the screen */
	mvwprintw(win, this->y, this->x, door_char);
	mvwprintw(win, this->y-1, this->x, door_char);
}

Door::Door(int x, int y, char id, char type) : Entity(x, y) {
    this->id = id;
    this->type = type;
}
void Door::draw(WINDOW* win) { }

