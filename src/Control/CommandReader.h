#ifndef INCLUDE_SRC_COMMANDREADER_H
#define INCLUDE_SRC_COMMANDREADER_H

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
		KeypadInput const *_keypad_input;
		bool (*_player_can_move_callback)(Player, Tile const&);
		Command _command;

	public:
		/**
		 * Initializes a new CommandReader instance.
		 * @param keypad_input - The hardware interface for reading coordinates from a keypad.
		 * @param player_can_move_callback - A callback that determines whether a given player is allowed to move.
		 */
		CommandReader(
			KeypadInput const *keypad_input,
			bool (player_can_move_callback)(Player, Tile const&));

		/**
		 * Resets the CommandReader by discarding the current user input.
		 */
		void reset();

		/**
		 * Retrieves user input from the hardware interfaces.
		 * This method must be continuously called, such as in the main loop() method.
		 * @return An input object describing the current user input.
		 */
		Command read();

	private:
		/** Main loop when this class is in state 'WaitingForCoord0'. */
		void read_WaitingForCoord0();
		/** Main loop when this class is in state 'WaitingForCoord1'. */
		void read_WaitingForCoord1();
		/** Main loop when this class is in state 'WaitingForPlayer'. */
		void read_WaitingForPlayer();
		/** Called when the user has requested the move for the given player. */
		void tryRequestMove(Player player);
};

#endif
