
#include "headers/option.h"
#include "headers/render.h"

int
main(int argc, char** argv)
{

	parseargs(argc, argv);

	curses_init();

	Renderer renderer(new MainScreen(40, 40, 0, 0));

	renderer.render_screen();
	while (1) {
		renderer.update_screen();
	}

	curses_exit();

	return 0;
}

