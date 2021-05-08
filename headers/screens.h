#ifndef __SCREENS_H__
#define __SCREENS_H__

#include <ncurses.h>

class Window {
	public:
		Window(int w, int h);
		~Window(void);
		virtual void update(void);
		virtual void render(void);
};

#endif // __SCREENS_H__
