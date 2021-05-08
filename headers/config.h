#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <player.h>

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



#endif // __CONFIG_H__
