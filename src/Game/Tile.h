#ifndef INCLUDE_SRC_GAME_TILE_H
#define INCLUDE_SRC_GAME_TILE_H

#include "../types.h"

/**
 * Structure representing a tile on the game board.
 */
struct Tile
{
	/* The horizontal zero-based index of the tile. */
	coord_t x;
	/* The vertical zero-based index of the tile. */
	coord_t y;

	Tile() : x(-1), y(-1) { }
	Tile(coord_t x, coord_t y) : x(x), y(y) { }
};

#endif
