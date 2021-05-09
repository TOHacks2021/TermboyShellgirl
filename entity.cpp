#include <iostream>
#include <string>
#include <vector>

#include "headers/render.h"
#include "headers/entity.h"
#include "headers/levelread.h"

char Player::active_color = ColouredEntity::RED;

Entity::~Entity() {}
void Entity::draw(WINDOW* win) { }
void Entity::update(Level* level) { }
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

void
Entity::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

Player::Player(int x, int y, char color)
: ColouredEntity(x, y, color)
{
	this->isJumping = false;
	this->jumpDistance = 0;
}

void
Player::draw(WINDOW* win)
{
	int hlcolor = COLOR_PAIR((ColouredEntity::RED == this->getColor()) ?  term_red : term_blue);
	
	wattron(win, hlcolor);
	wattron(win, A_BOLD);
	mvwprintw(win, this->y-1, this->x, "o");
	wattrset(win, 0);

	hlcolor = COLOR_PAIR((ColouredEntity::RED == this->getColor()) ?  term_red_bg : term_blue_bg);
	wattron(win, hlcolor);
	mvwprintw(win, this->y, this->x, " ");
	wattrset(win, 0);
}

void
Player::update(Level* level)
{
	this->moveVertical(level);
	if (this->getColor() != Player::active_color) return;

	int c;
	PlayerControls ctr = player_controls;

	timeout(200);

	c = getch();
	if (c == ctr.move_left) {
		this->moveLeft(level);
	} else if (c == ctr.move_right) {
		this->moveRight(level);
	} else if (c == ctr.move_up && false == this->isJumping) {
		this->isJumping = true;
		this->jumpDistance = PLAYER_JUMP_HEIGHT;
	} else if (c == ctr.switch_player) {
		Player::active_color = (Player::active_color == ColouredEntity::RED) ? ColouredEntity::BLUE : ColouredEntity::RED;
	} else if (c== ctr.quit_game) {
		curses_exit();
		exit(1);
	}
	this->checkDeath(level);

}

/* hardcoded wall blocks :< */
void
Player::moveLeft(Level* level)
{
	if (this->x <= 0) return;	
	if (level->getGrid()[this->x-1][this->y] == '#') return;
	if (level->getGrid()[this->x-1][this->y-1] == '#') return;
	this->x -= 1;
}

void
Player::moveRight(Level* level)
{
	if (this->x >= level->getLength()-1) return;
	if (level->getGrid()[this->x+1][this->y] == '#') return;
	if (level->getGrid()[this->x+1][this->y-1] == '#') return;
	this->x += 1;
}

void
Player::moveVertical(Level* level)
{ 	
	/* apply 'gravity' */
	if (0 >= this->jumpDistance && level->getGrid()[this->x][this->y+1] == ' ') {
		this->y += 1;
	}

	/* hit head on ceiling */
	if (level->getGrid()[this->x][this->y-1] != ' ') {
		this->jumpDistance = 0;
	}

	/* move up for jump */
	if (this->jumpDistance != 0) {
		this->y -= 1;
		this->jumpDistance -= 1;
	}

	/* reset jump if on group */
	if (level->getGrid()[this->x][this->y+1] != ' ')
		this->isJumping = false;
}

void
Player::startJump(Level* level)
{
	if (true == this->isJumping) return;
	this->isJumping = true;
	this->jumpDistance = PLAYER_JUMP_HEIGHT;
}

void
Player::checkDeath(Level* level)
{
	char block_under = level->getGrid()[this->x][this->y+1];

	if (
		'!' == block_under ||
		('~' == block_under && ColouredEntity::RED == this->getColor()) || 
		('^' == block_under && ColouredEntity::BLUE == this->getColor())
	) level->resetSpawn();
}

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
	wattron(win, A_BOLD);
	mvwprintw(win, this->y, this->x, "$");
	wattroff(win, hlcolor);
	wattroff(win, A_BOLD);
}

void Gem::update(Level* level) {
    int pos = -1;
    bool del = false;

    if (this->getColor() == ColouredEntity::RED && level->red_player->getX() == this->getX()
     && (level->red_player->getY() == this->getY() || level->red_player->getY() + 1 == this->getY())) {
         level->remove_red_gem();
         del = true;
    }

    else if (this->getColor() == ColouredEntity::BLUE && level->blue_player->getX() == this->getX()
     && (level->blue_player->getY() == this->getY() || level->blue_player->getY() + 1 == this->getY())) {
         level->remove_blue_gem();
         del = true;
    }
    

    for (int i = 0; i < level->entities.size(); i++) {
        Entity* e = level->entities.at(i);

        if (this == e) {
            pos = i;
        }
    }

    if (del) {
        level->entities.erase(level->entities.begin()+pos);
    }
}

ControlEntity::ControlEntity(int x, int y, char id)
: Entity(x, y)
{
	this->id = id;
	this->active = false;
}

bool ControlEntity::getActive() const {
    return active;
}
char ControlEntity::getId() const {
    return id;
}
void ControlEntity::setActive(bool a) {
    active = a;
}

void ControlEntity::draw(WINDOW* win) { }
void ControlEntity::update(Level* level) { }

PressurePlate::PressurePlate(int x, int y, char id) : ControlEntity(x, y, id) { }

void
PressurePlate::draw(WINDOW* win)
{ 
	mvwprintw(win, this->y, this->x, "=");
}
void PressurePlate::update(Level* level) {
    bool isPressed = false;
    if (level->red_player->getX() == this->getX() && level->red_player->getY() == this->getY()) {
        isPressed = true;
    }
    if (level->blue_player->getX() == this->getX() && level->blue_player->getY() == this->getY()) {
        isPressed = true;
    }
    for (Block* b: level->blocks) {
        if (b->getX() == this->getX() && b->getY() == this->getY()) {
            isPressed = true;
        }
    }
    this->setActive(isPressed);
}

Switch::Switch(int x, int y, char id) : ControlEntity(x, y, id) { }

void
Switch::draw(WINDOW* win)
{
	mvwprintw(win, this->y, this->x, this->getActive() ? "\\" : "/");
}

void Switch::update(Level* level) {
    
}

Block::Block(int x, int y) : Entity(x, y) { }

void
Block::draw(WINDOW* win)
{
	mvwprintw(win, this->y, this->x, "@");
}
void Block::update(Level* level) {

}

Exit::Exit(int x, int y, char color) : ColouredEntity(x, y, color) { }

void
Exit::draw(WINDOW* win)
{
	char* door_char = "";

	switch (this->getColor()) {
		case ColouredEntity::RED:
			door_char = "[";
			break;
		case ColouredEntity::BLUE:
			door_char = "]";
			break;
	}
	/* careful not to print off the screen */
	int hlcolor = COLOR_PAIR((ColouredEntity::RED == this->getColor()) ?  term_red : term_blue);
	wattron(win, hlcolor);
	mvwprintw(win, this->y-1, this->x, door_char);
	mvwprintw(win, this->y, this->x, door_char);
	wattroff(win, hlcolor);

}

void
Exit::update(Level* level)
{

}

Door::Door(int x, int y, char id, char type, char dir, int max_dist) : Entity(x, y) {
    this->id = id;
    this->type = type;
	this->dir = dir;
	this->max_dist = max_dist;
	this->cur_dist = 0;
}

void
Door::draw(WINDOW* win)
{
	switch (this->type) {
		case Door::C_L:
			for (int i = 0; i < DOOR_LENGTH; i++)
				mvwprintw(win, this->getY(), this->getX()+i, "@");
			break;
		case Door::C_U:
			for (int i = 0; i < DOOR_LENGTH; i++)
				mvwprintw(win, this->getY()-i, this->getX(), "@");
			break;
		case Door::C_R:
			for (int i = 0; i < DOOR_LENGTH; i++)
				mvwprintw(win, this->getY(), this->getX()-i, "@");
			break;
		case Door::C_D:
			for (int i = 0; i < DOOR_LENGTH; i++)
				mvwprintw(win, this->getY()+i, this->getX(), "@");
			break;
	}
}

void
Door::update(Level* level)
{
	if (
		(this->getActivated(level) && this->cur_dist < this->max_dist) ||
		(!this->getActivated(level) && this->cur_dist > 0)
	) {

		int direct_mult = this->getActivated(level) ? 1 : -1;
		this->cur_dist += direct_mult;

		switch (this->dir) {
			case Door::M_L:
				this->setPos(this->x-direct_mult, this->y);
				break;
			case Door::M_U:
				this->setPos(this->x, this->y-direct_mult);
				break;
			case Door::M_R:
				this->setPos(this->x+direct_mult, this->y);
				break;
			case Door::M_D:
				this->setPos(this->x, this->y+direct_mult);
				break;
			default:
				fprintf(stderr, "invlid dir enum");
		}

	}
}

char Door::getId() const { return this->id; }
char Door::getType() const { return this->type; }
char Door::getDir() const { return this->dir; }
int Door::getMaxDist() const { return this->max_dist; }

bool
Door::getActivated(Level* level)
{
	for (ControlEntity* controller : level->controllers) {
		/* printf("%c:%c ", this->getId(), controller->getId()); */
		if (toupper(controller->getId() == this->getId())) {
			return controller->getActive();
		}
	}
	return false;
}

