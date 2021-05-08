#include "headers/render.h"

void
curses_init(void)
{
	initscr();
	cbreak();
	/* curs_off(); */
	keypad(stdscr, TRUE);

	if (FALSE == has_colors()) {
		fprintf(stderr, "Your terminal does not support color.\n");
		exit(1);
	}

}

void
curses_exit(void)
{
	endwin();
}
