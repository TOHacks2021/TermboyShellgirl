#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "levelread.h"

#define PLAYER_JUMP_HEIGHT 4

const PlayerControls player_controls = {
	.move_up = 'w',
	.move_down = 's',
	.move_left = 'a',
	.move_right = 'd',
	.interact = 'x',
	.switch_player = ' ',
	.quit_game = 'q'
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

#define UI_HEIGHT 7
#define UI_PADDING 1

#endif // __CONFIG_H__
