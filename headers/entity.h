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

typedef struct PlayerControls {
	char move_up;
	char move_left;
	char move_right;
	char interact;	
} PlayerControls;

#endif // __ENTITY_H__
