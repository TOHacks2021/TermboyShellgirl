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
};

typedef struct LevelTiles {
    char empty;
	char wall;
	char lava;
	char water;
	char green_mud;
	char red_spawn;
	char blue_spawn;
	char red_exit;
	char blue_exit;
	char sw = '/';
	char pressure_plate = '=';
} LevelTiles;

#endif // __LEVELREAD_H__
