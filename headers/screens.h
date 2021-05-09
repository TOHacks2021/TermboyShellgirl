#ifndef __SCREENS_H__
#define __SCREENS_H__

class Screen;
class MainScreen;
class GameScreen;

#include <memory>
#include <cstdlib>
#include <string>
#include <ncurses.h>
#include <menu.h>
#include "config.h"
#include "utils.h"
#include "render.h"
#include "levelread.h"

class Screen {
	public:
		Screen(int w, int h, int y, int x);
		~Screen(void);
		virtual void update(void);
		virtual void render(void);
	protected:
		WINDOW* win;
};

class MainScreen : public Screen {
	public:
		MainScreen(int w, int h, int y, int x);
		void update(void) override;
		void render(void) override;
	private:
		MENU* menu;
};

class GameScreen : public Screen {
	public:
		GameScreen(int w, int h, int y, int x, std::string filepath);
		void update(void) override;
		void render(void) override;
	private:
		Level* level;
		WINDOW* ui_win;
};

#endif // __SCREENS_H__
