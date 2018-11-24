#ifndef INCLUDE_SRC_GAME_BOARD_H
#define INCLUDE_SRC_GAME_BOARD_H

#include "../types.h"
#include "Player.h"
#include "Tile.h"

/**
 * Represents a "Reversi" game board consisting of individual tiles.
 */
class Board
{
	private:
		coord_t const _width;
		coord_t const _height;
		Player * const _owners;

	public:
		/**
		 * Initializes a new Board instance.
		 * @param width - The number of tiles in the horizontal direction.
		 * @param height - The number of tiles in the vertical direction.
		 */
		Board(coord_t width, coord_t height);

		/**
		 * Frees all resources reserved by this instance.
		 */
		~Board();

		/**
		 * Gets the number of tiles in the horizontal direction.
		 */
		coord_t getWidth() const;

		/**
		 * Gets the number of tiles in the vertical direction.
		 */
		coord_t getHeight() const;

		/**
		 * Checks whether the given tile coordinates are still on the game board.
		 * @param tile - The coordinates of the tile to check.
		 * @returns Returns true iff the tile is on the board.
		 */
		bool contains(Tile const &tile) const;

		/**
		 * Gets the player who has conquered the given tile.
		 * @param tile - The coordinates of the tile.
		 */
		Player getTileOwner(Tile const &tile) const;

		/**
		 * Sets the player who has conquered the given tile.
		 * @param tile - The coordinates of the tile.
		 * @param owner - The new owner of the tile.
		 */
		void setTileOwner(Tile const &tile, Player owner);
};

#endif
