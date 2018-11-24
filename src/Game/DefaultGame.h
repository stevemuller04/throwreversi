#ifndef INCLUDE_SRC_GAME_DEFAULTGAME_H
#define INCLUDE_SRC_GAME_DEFAULTGAME_H

#include "Game.h"

/**
 * Default implementation of the Reversi game.
 * In this mode, each of the two players can play at all times (there is not control whose turn it is).
 * When a tile is conquered, then any adversial tiles surrounded by the newly placed tile and an existing own tile, are also conquered.
 */
class DefaultGame : public Game
{
	public:
		/**
		 * @see Game::beginRound()
		 */
		void beginRound() override;

		/**
		 * @see Game::playerCanMove()
		 */
		bool playerCanMove(Board const &board, Player player, Tile const &tile) const override;

		/**
		 * @see Game::playerMove()
		 */
		bool playerMove(Board &board, Player player, Tile const &tile, TileUpdate *updates, int &num_updates) override;
};

#endif
