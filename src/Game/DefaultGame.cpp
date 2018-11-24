#include "DefaultGame.h"

void DefaultGame::beginRound()
{
	// unused
}

bool DefaultGame::playerCanMove(Board const &board, Player player, Tile const &tile) const
{
	// Any player can move at all time
	// The neutral player ('None') can never move
	return
		player == Player::PlayerA ||
		player == Player::PlayerB;
}

bool DefaultGame::playerMove(Board &board, Player player, Tile const &tileOfMove, TileUpdate *updates, int &num_updates)
{
	num_updates = 0;

	// Make sure the tile is not owned by any player yet
	if (board.getTileOwner(tileOfMove) != Player::None)
		return false;

	// Conquer at least this tile
	updates[0].tile = tileOfMove;
	updates[0].owner = player;
	updates[0].previous_owner = Player::None;
	++num_updates;

	// Pick a direction
	for (int8_t dx = -1; dx <= 1; ++dx)
	for (int8_t dy = -1; dy <= 1; ++dy)
	if (dx != 0 || dy != 0) // vertically, horizontally, or diagonally
	{
		// Find the first tile in that direction which belongs to the current player
		Tile ptr;
		for (uint8_t d = 1; ; ++d)
		{
			// Determine the coordinates of the said tile
			ptr.x = tileOfMove.x + dx * d;
			ptr.y = tileOfMove.y + dy * d;
			// Check if the tile is still within the board
			if (!board.contains(ptr))
				break;

			// Determine the player who currently owns the tile
			Player tileOwner = board.getTileOwner(ptr);

			// Provisionally create a TileUpdate for this tile, as if the player conquered it,
			// but do not increment num_updates, so that the tile update is not official yet.
			updates[num_updates + d - 1].tile = ptr;
			updates[num_updates + d - 1].previous_owner = tileOwner;
			updates[num_updates + d - 1].owner = player;

			// If the tile does not belong to any player, then skip this direction;
			// in that case, all provisional tile updates are automatically discarded.
			if (tileOwner == Player::None)
				break;

			// If the tile belongs to the current player, he can conquer all tiles between this one and "tileOfMove".
			if (tileOwner == player)
			{
				// The tile updates have already been created; just need to commit.
				num_updates += d - 1;
				break;
			}
		}
	}

	// Update board
	for (int i = 0; i < num_updates; ++i)
		board.setTileOwner(updates[i].tile, updates[0].owner);

	// The move was legal
	return true;
}