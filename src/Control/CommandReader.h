#ifndef INCLUDE_SRC_CONTROL_COMMANDREADER_H
#define INCLUDE_SRC_CONTROL_COMMANDREADER_H

#include "../Input/KeypadInput.h"
#include "../Game/Player.h"
#include "../Game/Tile.h"
#include "Command.h"

/**
 * Class that interacts with the hardware for retrieving a command (= the user input).
 */
class CommandReader
{
	private:
		enum State
		{
			WaitingForCoord0,
			WaitingForCoord1,
			WaitingForPlayer,
		};

	private:
		State _state = State::WaitingForCoord0;
		KeypadInput &_keypad_input;
		Command _command;

	public:
		/**
		 * Initializes a new CommandReader instance.
		 * @param keypad_input - The hardware interface for reading coordinates from a keypad.
		 * @param player_can_move_callback - A callback that determines whether a given player is allowed to move.
		 */
		CommandReader(KeypadInput &keypad_input);

		/**
		 * Resets the CommandReader by discarding the current user input.
		 */
		void reset();

		/**
		 * Retrieves user input from the hardware interfaces.
		 * This method must be continuously called, such as in the main loop() method.
		 * Make sure to set a 'playerCanMove' callback via the setPlayerCanMoveCallback() method.
		 * @return An input object describing the current user input.
		 */
		Command update();

	private:
		/** Main loop when this class is in state 'WaitingForCoord0'. */
		void update_WaitingForCoord0();
		/** Main loop when this class is in state 'WaitingForCoord1'. */
		void update_WaitingForCoord1();
		/** Main loop when this class is in state 'WaitingForPlayer'. */
		void update_WaitingForPlayer();
		/** Called when the user has requested the move for the given player. */
		void tryRequestMove(Player player);
};

#endif
