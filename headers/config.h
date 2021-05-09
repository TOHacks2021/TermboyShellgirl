#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "levelread.h"

/* #define PLAYER_1_UP 'w' */
/* #define PLAYER_1_DOWN 's' */
/* #define PLAYER_1_LEFT 'a' */
/* #define PLAYER_1_RIGHT 'd' */
/* #define PLAYER_1_INTERACT 'e' */

/* #define PLAYER_2_UP 'k' */
/* #define PLAYER_2_DOWN 'j' */
/* #define PLAYER_2_LEFT 'h' */
/* #define PLAYER_2_RIGHT 'l' */
/* #define PLAYER_2_INTERACT 'i' */

#define PLAYER_JUMP_HEIGHT 3

const PlayerControls player1_controls = {
	.move_up = 'w',
	.move_down = 's',
	.move_left = 'a',
	.move_right = 'd',
	.interact = 'x'
};

const PlayerControls player2_controls = {
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

#define UI_HEIGHT 7
#define UI_PADDING 1


#endif // __CONFIG_H__
