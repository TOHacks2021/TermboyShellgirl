#include "headers/render.h"

/* Renderer */
Renderer::Renderer(Screen* default_screen)
{
	this->screen = default_screen;
}

void
Renderer::render_screen(void)
{
	this->screen->render();
}

void
Renderer::update_screen(void)
{
	this->screen->update();
}

/* helper funcs */
void
curses_init(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
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
