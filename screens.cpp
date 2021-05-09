#include "headers/screens.h"

/* screen */
Screen::Screen(int h, int w, int y, int x)
{
	this->win = newwin(h, w, y, x);
	refresh();
}

Screen::~Screen(void)
{
	delwin(this->win);	
}

void Screen::update(void) { }
void Screen::render(void) { }

/* main screen */
typedef struct MenuInfo {
	char* label;
	void (*func)(WINDOW*);
} MenuInfo;

void play_button(WINDOW*);
void help_button(WINDOW*);
void quit_button(WINDOW*);

const MenuInfo menu_info[] = {
	{ "Play", &play_button },
	{ "Help", &help_button },
	{ "Quit", &quit_button },
	0,
};

MainScreen::MainScreen(int h, int w, int y, int x)
: Screen(h, w, y, x)
{
	ITEM** menuitems;
	int menu_info_length = array_length(MenuInfo*, menu_info);

	/* init menu items array */
	menuitems = (ITEM**)malloc((menu_info_length+1)*sizeof(ITEM*));
	for (int i = 0; i < menu_info_length; i++) {
		menuitems[i] = new_item(menu_info[i].label, "");
		set_item_userptr(menuitems[i], (void*)menu_info[i].func);
	}
	menuitems[menu_info_length] = NULL;

	this->menu = new_menu(menuitems);
	post_menu(this->menu);
	wrefresh(this->win);
	refresh();
}

void
MainScreen::update(void)
{
	int c;

	c = getch();
	switch (c) {
		case player1_controls.move_up:
		case player2_controls.move_up:
			menu_driver(this->menu, REQ_UP_ITEM);
			break;
		case player1_controls.move_down:
		case player2_controls.move_down:
			menu_driver(this->menu, REQ_DOWN_ITEM);
			break;
		case player1_controls.interact:
		case player2_controls.interact:
			{
				ITEM* curitem;
				void (*callback)(WINDOW*);

				curitem = current_item(this->menu);
				callback = (void(*)(WINDOW*))item_userptr(curitem);
				callback(this->win);
			}
			break;
	}

}

void
MainScreen::render(void)
{
	wrefresh(this->win);
}

void
play_button(WINDOW* win)
{
	/* mvwprintw(win, 10, 10, "play"); */
	/* wrefresh(win); */
	(Renderer::renderer)->switch_screen(new GameScreen(40, 40, 0, 0, "levels/level1"));
}

void
help_button(WINDOW* win)
{
	mvwprintw(win, 10, 10, "help");
	wrefresh(win);
}

void
quit_button(WINDOW* win)
{
	mvwprintw(win, 10, 10, "quit");
	wrefresh(win);
}

/* game screen */
GameScreen::GameScreen(int h, int w, int y, int x, std::string filepath)
: Screen(h, w, y, x)
{
	this->level = new Level(filepath);
}

void
GameScreen::update(void)
{

}

void
GameScreen::render(void)
{
	for (auto entity : this->level->entities) {
		entity.draw(this->win);
	}
	wrefresh(this->win);
}

