#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity {
	public:
		virtual ~Entity();
		virtual void draw();
	protected:
		Entity(int x, int y);
	private:
		int x, y;
};

class Player: public Entity {
    public:
        Player (int x, int y);
        void draw() override;
};

typedef struct PlayerControls {
	const char move_up;
	const char move_down;
	const char move_left;
	const char move_right;
	const char interact;	
} PlayerControls;


#endif // __ENTITY_H__
