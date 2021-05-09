#ifndef __RENDER_H__
#define __RENDER_H__

class Renderer;

#include <cstdio>
#include <cstdlib>
#include <ncurses.h>
#include "screens.h"

class Renderer {

	public:
		static Renderer* renderer;
		static void init_renderer(Screen* default_screen);
		void render_screen(void);		
		void update_screen(void);
		void switch_screen(Screen* new_screen);
	private:
		Renderer(Screen* default_screen);
		Screen* screen;
};

/* Renderer* Renderer::renderer; */

extern void curses_init(void);
extern void curses_exit(void);

#endif // __RENDER_H__
