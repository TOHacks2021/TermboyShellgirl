
#include "headers/option.h"
#include "headers/render.h"

int
main(int argc, char** argv)
{

	parseargs(argc, argv);

	curses_init();

	int scr_h, scr_w;
	getmaxyx(stdscr, scr_h, scr_w);

	Renderer::init_renderer(new MainScreen(scr_h, scr_w, 0, 0));

	while (1) {
		(Renderer::renderer)->render_screen();
		(Renderer::renderer)->update_screen();
	}

	curses_exit();

	return 0;
}

