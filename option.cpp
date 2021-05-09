
#include <cstdio>
#include <string>
#include <getopt.h>

#include "headers/levelread.h"
#include "headers/option.h"

typedef struct option option;

option long_options[] = {
	{"help", no_argument, 0, 'h'},
	{"file", required_argument, 0, 'f'},
	{0, 0, 0, 0}
};

void
parseargs(int argc, char** argv)
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
				{
					Level* level = new Level(std::string(optarg));
					level->draw();
					/* printf("file option with value %s\n", optarg); */

				}
				break;
			case '?':
				printf("invalid input\n");
				break;
			default:
				printf("default\n");
		}
	}
}

