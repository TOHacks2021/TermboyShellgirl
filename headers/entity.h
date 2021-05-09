#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <ncurses.h>

class Entity {
	public:
		virtual ~Entity();
		virtual void draw(WINDOW* win);

		int getX() const;
		int getY() const;
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
        Player(int x, int y, char color);
        void draw(WINDOW* win) override;
};

class Gem: public ColouredEntity {
    public:
        Gem(int x, int y, char color);
        void draw(WINDOW* win) override;
};

class PressurePlate: public Entity {
	public:
		PressurePlate(int x, int y, char id);
		void draw(WINDOW* win) override;

		char getId() const;
		bool getActive() const;
		void setActive(bool active);
	
	private:
		char id;
		bool active = false;
};

class Switch: public Entity {
	public:
		Switch(int x, int y, char id);
		void draw(WINDOW* win) override;

		char getId() const;
		bool getActive() const;
		void setActive(bool active);
	private:
		char id;
		bool active = false;
};

class Block: public Entity {
	public:
		Block(int x, int y);
		void draw(WINDOW* win) override;
};

class Exit: public ColouredEntity {
	public:
		Exit(int x, int y, char color);
		void draw(WINDOW* win) override;
};

class Door: public Entity {
	public:
		Door(int x, int y, char id, char type);
		void draw(WINDOW* win) override;

		char getId() const;
		char getType() const;

	private:
		char id;
		char type;
};


typedef struct PlayerControls {
	const char move_up;
	const char move_down;
	const char move_left;
	const char move_right;
	const char interact;	
} PlayerControls;


#endif // __ENTITY_H__
