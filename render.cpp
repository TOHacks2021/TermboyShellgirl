#include "headers/render.h"

Renderer* Renderer::renderer = nullptr;

void
Renderer::init_renderer(Screen* default_screen)
{
	if (nullptr != Renderer::renderer) {
		fprintf(stderr, "Attempting to initialized global renderer twice.\n");
		exit(1);
	}
	Renderer::renderer = new Renderer(default_screen);	
	clear();
	refresh();
}

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

void
Renderer::switch_screen(Screen* new_screen)
{
	/* delete this->screen; */
	this->screen = new_screen;
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
	start_color();
	curses_colors();
}

void
curses_colors(void)
{
	init_pair(term_red, COLOR_RED, COLOR_BLACK);
	init_pair(term_blue, COLOR_BLUE, COLOR_BLACK);
	init_pair(term_water, COLOR_WHITE, COLOR_CYAN);
	init_pair(term_lava, COLOR_BLACK, COLOR_RED);
	init_pair(term_poison, COLOR_BLACK, COLOR_GREEN);
	init_pair(term_wall, COLOR_BLACK, COLOR_WHITE);
}

void
curses_exit(void)
{
	endwin();
}
