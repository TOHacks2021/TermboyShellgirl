#ifndef __ENTITY_H__
#define __ENTITY_H__

class Enitity;
class ColouredEntity;
class Player;
class Gem;
class ControlEntity;
class PressurePlate;
class Switch;
class Block;
class Exit;
class Door;


#include <ncurses.h>
#include "levelread.h"

typedef struct PlayerControls {
	char move_up;
	char move_down;
	char move_left;
	char move_right;
	char interact;	
	char switch_player;
	char quit_game;
} PlayerControls;

class Entity {
	public:
		virtual ~Entity();
		virtual void draw(WINDOW* win);
		virtual void update(Level* level);

		int getX() const;
		int getY() const;
		void setPos(int x, int y);
	protected:
		Entity(int x, int y);
		int x, y;
};

class ColouredEntity: public Entity {
	public:
		static const char RED = 'r';
		static const char BLUE = 'b';

		char getColor() const;
	protected:
		ColouredEntity(int x, int y, char color);

	private:
		char color;

};

class Player: public ColouredEntity {
    public:
		static char active_color;

        Player(int x, int y, char color);
        void draw(WINDOW* win) override;
		void update(Level* level) override;
	private:
		bool gravStep;
		bool isJumping;
		int jumpDistance;
		void moveLeft(Level* level);
		void moveRight(Level* level);
		void moveVertical(Level* level);
		void startJump(Level* level);
		void applyJump(Level* level);
		void checkDeath(Level* level);
};

class Gem: public ColouredEntity {
    public:
        Gem(int x, int y, char color);
        void draw(WINDOW* win) override;
		void update(Level* level) override;
};

class ControlEntity: public Entity {
	public:
		ControlEntity(int x, int y, char id);
		void draw(WINDOW* win) override;
		void update(Level* level) override;

		char getId() const;
		bool getActive() const;
		void setActive(bool active);
	
	private:
		char id;
		bool active;

};

class PressurePlate: public ControlEntity {
	public:
		PressurePlate(int x, int y, char id);
		void draw(WINDOW* win) override;
		void update(Level* level) override;
};

class Switch: public ControlEntity {
	public:
		Switch(int x, int y, char id);
		void draw(WINDOW* win) override;
		void update(Level* level) override;
};

class Block: public Entity {
	public:
		Block(int x, int y);
		void draw(WINDOW* win) override;
		void update(Level* level) override;
};

class Exit: public ColouredEntity {
	public:
		Exit(int x, int y, char color);
		void draw(WINDOW* win) override;
		void update(Level* level) override;
};

#define DOOR_LENGTH 8

class Door: public Entity {
	public:
		Door(int x, int y, char id, char type, char dir, int max_dist);
		void draw(WINDOW* win) override;
		void update(Level* level) override;

		char getId() const;
		char getType() const;
		char getDir() const;
		int getMaxDist() const;
		bool getActivated(Level* level);

		static const char C_L = '0';
		static const char C_U = '1';
		static const char C_R = '2';
		static const char C_D = '3';

		static const char M_L = '4';
		static const char M_U = '5';
		static const char M_R = '6';
		static const char M_D = '7';

	private:
		char id;
		char type;
		char dir;
		int max_dist;
		int cur_dist;
};



#endif // __ENTITY_H__
