#include "GodmodeGame.h"

void GodmodeGame::beginRound()
{
	// unused
}

bool GodmodeGame::playerCanMove(Board const &board, Player player, Tile const &tile) const
{
	// Any player can play at all time, even the neutral player ('None')
	return true;
}

bool GodmodeGame::playerMove(Board &board, Player player, Tile const &tile, TileUpdate* updates, int &num_updates)
{
	// In god mode, we only change the owner of the given tile; there is no further game logic

	// Check if the owner is really changed
	Player const owner = board.getTileOwner(tile);
	if (owner != player)
	{
		// Change the tile owner
		board.setTileOwner(tile, player);

		// There is only one tile update 
		num_updates = 1;
		updates[0].tile = tile;
		updates[0].owner = player;
		updates[0].previous_owner = owner;

		return true;
	}
	else
		return false;
}
