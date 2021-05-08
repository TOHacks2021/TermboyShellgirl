#ifndef __LEVELREAD_H__
#define __LEVELREAD_H__

#include <string>
#include <vector>
#include <iostream>

#include "entity.h"

class Level {
	public:
		virtual ~Level();
		virtual void draw();
        char** getGrid() const;
		Level(std::string filename);
	private:
		char** grid;
        int time; 
        int length, height;
		std::vector<Entity> entities;
        void parseFile(std::string filename);
        int red_gems_remaining, blue_gems_remaining;
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
