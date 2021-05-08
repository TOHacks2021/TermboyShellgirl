#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "levelread.h"

const PlayerControls player1_controls = {
	.move_up = 'w',
	.move_left = 'a',
	.move_right = 'd',
	.interact = 'x'
};

const PlayerControls player2_controls = {
	.move_up = 'k',
	.move_left = 'h',
	.move_right = 'l',
	.interact = 'j'
};

const LevelTiles tiles = {
	.empty = ' ',
	.wall = '#',
	.lava = 'L',
	.water = 'W',
	.green_mud = 'G',
	.red_spawn = '1',
	.blue_spawn = '2',
	.red_exit = '3',
	.blue_exit = '4',
	.sw = '/',
	.pressure_plate = '='

};



#endif // __CONFIG_H__
