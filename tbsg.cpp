
#include "headers/option.h"
#include "headers/render.h"

int
main(int argc, char** argv)
{
	parseargs(argc, argv);

	curses_init();
	getch();
	curses_exit();

	return 0;
}

