#ifndef INCLUDE_SRC_GAME_TILEUPDATE_H
#define INCLUDE_SRC_GAME_TILEUPDATE_H

#include "Tile.h"
#include "Player.h"

/**
 * Structure representing an update of a tile during a game.
 */
struct TileUpdate
{
	/* The tile that has been updated. */
	Tile tile;
	/* The owner of the tile before the update. */
	Player previous_owner;
	/* The owner of the tile after the update. */
	Player owner;
};

#endif
