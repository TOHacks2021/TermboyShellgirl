#ifndef __RENDER_H__
#define __RENDER_H__

#include <cstdio>
#include <cstdlib>
#include <ncurses.h>
#include "screens.h"

class Renderer {
	public:
		Renderer(Screen* default_screen);
		void render_screen(void);		
		void update_screen(void);
	private:
		Screen* screen;
};

extern void curses_init(void);
extern void curses_exit(void);

#endif // __RENDER_H__
