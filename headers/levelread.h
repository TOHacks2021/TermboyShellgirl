#ifndef __LEVELREAD_H__
#define __LEVELREAD_H__

#include <vector>
#include "headers/entity.h"

class Level {
	public:
		virtual ~Level ();
		virtual void draw();
        char** getGrid () const;
	protected:
		Level (string filename);
	private:
		char** grid;
        int time;
        vector<Entity> entities;
};


#endif // __LEVELREAD_H__
