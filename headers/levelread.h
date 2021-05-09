#ifndef __LEVELREAD_H__
#define __LEVELREAD_H__

class Level;

#include <string>
#include <vector>
#include <iostream>
#include "entity.h"

class Level {
	public:
		std::vector<Entity*> entities;
		Level(std::string filename);
		~Level();
		void draw();
        char** getGrid() const;
		int getLength() const;
		int getHeight() const;
		void update();
		void remove_red_gem();
		void remove_blue_gem();
		void resetSpawn();
		Player* red_player;
		Player* blue_player;
        int red_gems_remaining, blue_gems_remaining;
		std::string filename;
		std::vector<Block*> blocks;
		Exit* red_exit;
		Exit* blue_exit;

	private:
		char** grid;
        int time; 
        int length, height;
        void parseFile(std::string filename);
        int red_spawn_x, red_spawn_y;
        int blue_spawn_x, blue_spawn_y;
};

typedef struct LevelTiles {
    const char empty;
	const char wall;
	const char lava;
	const char water;
	const char green_mud;
	const char red_spawn;
	const char blue_spawn;
	const char red_exit;
	const char blue_exit;
	const char sw;
	const char pressure_plate;
    const char red_gem;
    const char blue_gem;
    const char block;

} LevelTiles;

#endif // __LEVELREAD_H__
