
#include <cstdio>
#include <string>
#include <getopt.h>

#include "headers/levelread.h"
#include "headers/render.h"
#include "headers/screens.h"

typedef struct option option;

option long_options[] = {
	{"help", no_argument, 0, 'h'},
	{"file", required_argument, 0, 'f'},
	{0, 0, 0, 0}
};

void gameloop(std::string filename);

int
main(int argc, char** argv)
{
	int c;
	int option_index;

	while (1) {

		option_index = 0;
		c = getopt_long(argc, argv, "hf:", long_options, &option_index);

		if (-1 == c) break;

		switch (c) {
			case 'h':
				printf("help option\n");
				break;
			case 'f':
				gameloop(std::string(optarg));
				break;
			case '?':
				printf("invalid input\n");
				break;
			default:
				printf("default\n");
		}
	}

	return 0;
}

void
gameloop(std::string filename)
{
	curses_init();

	int scr_h, scr_w;
	getmaxyx(stdscr, scr_h, scr_w);

	Renderer::init_renderer(new GameScreen(scr_h, scr_w, 0, 0, filename));

	while (1) {
		(Renderer::renderer)->render_screen();
		(Renderer::renderer)->update_screen();
	}

	curses_exit();
}
