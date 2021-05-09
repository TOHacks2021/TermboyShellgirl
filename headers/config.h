#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "levelread.h"

constexpr PlayerControls player1_controls = {
	.move_up = 'w',
	.move_down = 's',
	.move_left = 'a',
	.move_right = 'd',
	.interact = 'x'
};

constexpr PlayerControls player2_controls = {
	.move_up = 'k',
	.move_down = 'j',
	.move_left = 'h',
	.move_right = 'l',
	.interact = 'i'
};

constexpr LevelTiles tiles = {
	.empty = ' ',
	.wall = '#',
	.lava = '^',
	.water = '~',
	.green_mud = '!',
	.red_spawn = '1',
	.blue_spawn = '2',
	.red_exit = '[',
	.blue_exit = ']',
	.sw = '/',
	.pressure_plate = '=',
	.red_gem = '<',
	.blue_gem = '>',
	.block = '@'

};



#endif // __CONFIG_H__
