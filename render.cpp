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

}

void
curses_exit(void)
{
	endwin();
}
