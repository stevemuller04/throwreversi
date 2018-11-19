#ifndef INCLUDE_SRC_GAME_TILE_H
#define INCLUDE_SRC_GAME_TILE_H

#include "../types.h"

#define TILE_COORD_UNDETERMINED -1

/**
 * Structure representing a tile on the game board.
 */
struct Tile
{
	/* The horizontal zero-based index of the tile. */
	coord_t x;
	/* The vertical zero-based index of the tile. */
	coord_t y;

	Tile() : x(TILE_COORD_UNDETERMINED), y(TILE_COORD_UNDETERMINED) { }
	Tile(coord_t x, coord_t y) : x(x), y(y) { }

	static Tile const Undetermined;
};

#endif
