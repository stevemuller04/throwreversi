#ifndef INCLUDE_SRC_CONTROL_Command_H
#define INCLUDE_SRC_CONTROL_Command_H

#include <Arduino.h>
#include "../Game/Player.h"
#include "../Game/Tile.h"

/**
 * Represents user input from the user.
 */
struct Command
{
	/**
	 * The tile selected by the user. Might not be fully determined.
	 */
	Tile selected_tile;

	/**
	 * The player selected by the user, or Player::None if no player is selected yet.
	 */
	Player selected_player;

	/**
	 * Whether the input has changed since the last time.
	 */
	bool has_changed;

	/**
	 * Whether the input is considered as being complete.
	 */
	bool is_complete;

	static Command const Empty;
};

#endif
