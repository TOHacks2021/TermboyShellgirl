#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity {
	public:
		virtual ~Entity();
		virtual void draw();

		int getX() const;
		int getY() const;
	protected:
		Entity(int x, int y);
	private:
		int x, y;
};

class Player: public Entity {
    public:
        Player(int x, int y, char color);
        void draw() override;

		static const char RED = 'r';
		static const char BLUE = 'b';
	
		char getColor() const;
	private:
		char color;

};

class Gem: public Entity {
    public:
        Gem(int x, int y, char color);
        void draw() override;

		static const char RED = 'r';
		static const char BLUE = 'b';

		char getColor() const;

	private:
		char color;

};

class PressurePlate: public Entity {
	public:
		PressurePlate(int x, int y, char id);
		void draw() override;

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
		void draw() override;
	private:
		char id;
		bool active = false;
};

class Door: public Entity {
	public:
		Door(int x, int y, char orientaion, char direction, char id);
		void draw() override;

		static const char VER_DIR = '0';
		static const char HOR_DIR = '1';
		static const char VER_OR = '2';
		static const char HOR_OR = '3';

	private:
		char orientation, direction, id;
		int position = 0;
};

typedef struct PlayerControls {
	const char move_up;
	const char move_down;
	const char move_left;
	const char move_right;
	const char interact;	
} PlayerControls;


#endif // __ENTITY_H__
