#ifndef INCLUDE_SRC_GAME_GODMODEGAME_H
#define INCLUDE_SRC_GAME_GODMODEGAME_H

#include "Game.h"

/**
 * Implementation of the Reversi game, where a referee can set the tile owner of each tile individually, without triggering the game logic.
 * In this mode, there is no concept of turns (everyone can play at all time) nor of conquering tiles.
 */
class GodmodeGame : public Game
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
