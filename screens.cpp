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
MainScreen::MainScreen(int h, int w, int y, int x)
: Screen(h, w, y, x)
{
	ITEM** menuitems;
	int menu_text_length = 3;
	const char* menu_text[] = {
		"Play",
		"Help",
		"Quit"
	};

	menuitems = (ITEM**)malloc((menu_text_length+1)*sizeof(ITEM*));
	for (int i = 0; i < menu_text_length; i++)
		menuitems[i] = new_item(menu_text[i], "");
	menuitems[menu_text_length] = NULL;

	this->menu = new_menu(menuitems);
	post_menu(this->menu);
	refresh();
}

void
MainScreen::update(void)
{
	int c;

	c = getch();
	switch (c) {
		/* case player1_controls.move_up: */
		/* case player2_controls.move_up: */
		case 'k':
			menu_driver(this->menu, REQ_UP_ITEM);
			break;
		/* case player1_controls.move_down: */
		/* case player2_controls.move_down: */
		case 'j':
			menu_driver(this->menu, REQ_DOWN_ITEM);
			break;
	}

}

void
MainScreen::render(void)
{
	mvwprintw(this->win, 0, 0, "pee");

	wrefresh(this->win);
}

