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
	/* int c; */

	/* c = getch(); */
	/* if (c == ctr1.move_up || c == ctr2.move_up) { */

	/* } */
	/* switch (c) { */
	/* 	case player1_controls.move_up: */
	/* 	case player2_controls.move_up: */
	/* 		menu_driver(this->menu, REQ_UP_ITEM); */
	/* 		break; */
	/* 	case player1_controls.move_down: */
	/* 	case player2_controls.move_down: */
	/* 		menu_driver(this->menu, REQ_DOWN_ITEM); */
	/* 		break; */
	/* 	case player1_controls.interact: */
	/* 	case player2_controls.interact: */
	/* 		{ */
	/* 			ITEM* curitem; */
	/* 			void (*callback)(WINDOW*); */

	/* 			curitem = current_item(this->menu); */
	/* 			callback = (void(*)(WINDOW*))item_userptr(curitem); */
	/* 			callback(this->win); */
	/* 		} */
	/* 		break; */
	/* } */

}

void
MainScreen::render(void)
{
	wrefresh(this->win);
}

void
play_button(WINDOW* win)
{
	int scr_h, scr_w;
	getmaxyx(stdscr, scr_h, scr_w);

	(Renderer::renderer)->switch_screen(new GameScreen(scr_h, scr_w, 0, 0, "levels/level1"));
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

	this->ui_win = derwin(this->win, UI_HEIGHT, w-2*UI_PADDING, h-UI_HEIGHT-UI_PADDING, UI_PADDING);
	wrefresh(this->win);
	refresh();
}

void
GameScreen::update(void)
{
	for (Entity* entity : this->level->entities) {
		entity->update(this->level);
	}
	for (Door* door: this->level->doors) {
		door->update(this->level);
	}
	this->level->red_player->update(this->level);
	this->level->blue_player->update(this->level);
	for (Block* block: this->level->blocks) {
		block->update(this->level);
	}
	this->level->red_exit->update(this->level);
	this->level->blue_exit->update(this->level);

	/* check level win condition */
	if (
		this->level->red_player->getX() == this->level->red_exit->getX() &&
		this->level->red_player->getY() == this->level->red_exit->getY() &&
		this->level->blue_player->getX() == this->level->blue_exit->getX() &&
		this->level->blue_player->getY() == this->level->blue_exit->getY()
	) {
		/* completed level */	
		curses_exit();
		exit(1);
	}
}

void
GameScreen::render(void)
{
	char** grid = this->level->getGrid();

	wclear(this->win);

	for (int i = 0; i < this->level->getLength(); i++) {
		for (int j = 0; j < this->level->getHeight(); j++) {

			char display_char = '?';

			switch (grid[i][j]) {
				case ' ':
					display_char= ' ';
					break;
				case '#':
					display_char = ' ';
					wattron(this->win, COLOR_PAIR(term_wall));
					break;
				case '~':
					display_char = ' ';
					wattron(this->win, COLOR_PAIR(term_water));
					wattron(this->win, A_BOLD);
					break;
				case '^':
					display_char = ' ';
					wattron(this->win, COLOR_PAIR(term_lava));
					wattron(this->win, A_BOLD);
					break;
				case '!':
					display_char = ' ';
					wattron(this->win, COLOR_PAIR(term_poison));
					wattron(this->win, A_BOLD);
					break;
				default:
					continue;
			}

			char str[2] = {display_char, '\0'};
			mvwprintw(this->win, j, i, str);
			wattrset(this->win, 0);
		}
	}

	for (Entity* entity : this->level->entities) {
		entity->draw(this->win);
	}
	for (Door* door: this->level->doors) {
		door->draw(this->win);
	}
	this->level->red_player->draw(this->win);
	this->level->blue_player->draw(this->win);
	for (Block* block: this->level->blocks) {
		block->draw(this->win);
	}
	this->level->red_exit->draw(this->win);
	this->level->blue_exit->draw(this->win);

	/* render ui */
	wclear(this->ui_win);
	box(this->ui_win, 0 ,0);
	mvwprintw(this->ui_win, 1, 2, "Level: %s", strToChar(this->level->filename));
	mvwprintw(this->ui_win, 2, 2, "current player: ");
	if (Player::active_color == ColouredEntity::RED) {
		wattron(this->ui_win, COLOR_PAIR(term_red));
		wprintw(this->ui_win, "RED");
		wattroff(this->ui_win, COLOR_PAIR(term_red));
	} else {
		wattron(this->ui_win, COLOR_PAIR(term_blue));
		wprintw(this->ui_win, "BLUE");
		wattroff(this->ui_win, COLOR_PAIR(term_blue));
	}
	mvwprintw(this->ui_win, 3, 2, "Red Gems Left: %d", this->level->red_gems_remaining);
	mvwprintw(this->ui_win, 4, 2, "Blue Gems Left: %d", this->level->blue_gems_remaining);


	wrefresh(this->win);
}

