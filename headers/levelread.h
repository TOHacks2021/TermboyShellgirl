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
        char[][] getGrid() const;
		Level(std::string filename);
	private:
		char[][] grid;
        int time; 
		std::vector<Entity> entities;
        void parseFile(std::string filename);
};

#endif // __LEVELREAD_H__
