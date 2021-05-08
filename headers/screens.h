#ifndef __SCREENS_H__
#define __SCREENS_H__

#include <memory>
#include <cstdlib>
#include <ncurses.h>
#include <menu.h>
#include "config.h"

class Screen {
	public:
		Screen(int w, int h, int y, int x);
		virtual void update(void);
		virtual void render(void);
	protected:
		WINDOW* win;
		~Screen(void);
};

class MainScreen : public Screen {
	public:
		MainScreen(int w, int h, int y, int x);
		void update(void) override;
		void render(void) override;
	private:
		MENU* menu;
};

#endif // __SCREENS_H__
