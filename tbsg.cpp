
#include "headers/option.h"
#include "headers/render.h"

int
main(int argc, char** argv)
{

	parseargs(argc, argv);

	curses_init();

	Renderer::init_renderer(new MainScreen(40, 40, 0, 0));

	while (1) {
		(Renderer::renderer)->render_screen();
		(Renderer::renderer)->update_screen();
	}

	curses_exit();

	return 0;
}

