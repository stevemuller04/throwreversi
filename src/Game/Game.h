#ifndef INCLUDE_SRC_GAME_GAME_H
#define INCLUDE_SRC_GAME_GAME_H

#include "Board.h"
#include "Player.h"
#include "TileUpdate.h"

/**
 * Describes the state of the game and provides methods to make player moves.
 */
class Game
{
	public:
		/**
		 * Begin the first/next round of the game.
		 * This method must be called before any moves are made.
		 */
		virtual void beginRound() = 0;

		/**
		 * Checks if the given player can currently make a move.
		 * @param board - The game board representing the current game status, and on which the move shall be made.
		 * @param player The player who is currently drawing.
		 * @param tile - The tile which the player has selected to make his next move.
		 * @return - Returns true iff the given player can move.
		 */
		virtual bool playerCanMove(Board const &board, Player player, Tile const &tile) const = 0;

		/**
		 * Tries to perform a player's move.
		 * @param board - The game board representing the current game status, and on which the move shall be made.
		 * @param player The player who is currently drawing.
		 * @param tile - The tile which the player has selected to make his next move.
		 * @param updates - A buffer for TileUpdate instances.
		 * This function will populate this array with the tile ownership changes resulting from the player's move.
		 * The array must be initialised before calling this function, and it must have enough elements (such as 2*(board width+board height)).
		 * @param num_updates - After the function call, this variable will contain the number of updates written to "updates".
		 * The value passed to this function will be ignored.
		 * @return - Returns true iff the move was legal, regardless of whether it had any effect.
		 */
		virtual bool playerMove(Board &board, Player player, Tile const &tile, TileUpdate* updates, int &num_updates) = 0;
};

#endif
