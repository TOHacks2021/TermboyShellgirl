#include "headers/option.h"

#include <getopt.h>

typedef struct option option;

option long_options[] = {
	{"help", no_argument, 0, 'h'},
	{"file", required_argument, 0, 'f'}
};

void
parseargs(char* filename)
{

}

