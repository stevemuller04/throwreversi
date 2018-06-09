#ifndef INCLUDE_SRC_CONTROLLER_H
#define INCLUDE_SRC_CONTROLLER_H

#include "Input/KeypadInput.h"
#include "Input/BoolPinInput.h"
#include "Output/BoolPinOutput.h"
#include "Game/Player.h"
#include "Game/Tile.h"

/**
 * Controller that interacts with the hardware for processing the user input.
 */
class Controller
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
		BoolPinInput const *_playerA_input;
		BoolPinInput const *_playerB_input;
		BoolPinInput const *_playerX_input;
		BoolPinOutput *_playerA_output;
		BoolPinOutput *_playerB_output;
		BoolPinOutput *_playerX_output;
		bool (*_player_can_move_callback)(Player, Tile const&);
		void (*_move_requested_callback)(Player, Tile const&);
		Tile _read_coords;

	public:
		/**
		 * Initializes a new Controller instance.
		 * @param keypad_input - The hardware interface for reading coordinates from a keypad.
		 * @param playerA_input - The hardware interface for the button that makes a move for player A.
		 * @param playerB_input - The hardware interface for the button that makes a move for player B.
		 * @param playerX_input - The hardware interface for the button that makes a move for the neutral player ('None').
		 * @param playerA_output - The hardware interface for the LED that displays if a move for player A is possible.
		 * @param playerB_output - The hardware interface for the LED that displays if a move for player B is possible.
		 * @param playerX_output - The hardware interface for the LED that displays if a move for the neutral player ('None') is possible.
		 * @param player_can_move_callback - A callback that determines whether a given player is allowed to move.
		 * @param move_requested_callback - A callback that is called when a player move has been requested by the user via the hardware interfaces.
		 */
		Controller(
			KeypadInput const *keypad_input,
			BoolPinInput const *playerA_input,
			BoolPinInput const *playerB_input,
			BoolPinInput const *playerX_input,
			BoolPinOutput *playerA_output,
			BoolPinOutput *playerB_output,
			BoolPinOutput *playerX_output,
			bool (player_can_move_callback)(Player, Tile const&),
			void (move_requested_callback)(Player, Tile const&));

		/**
		 * Resets the controller by discarding the current user input.
		 */
		void reset();

		/**
		 * Retrieves user input from the hardware interfaces.
		 * This method must be continuously called, such as in the main loop() method.
		 */
		void loop();

	private:
		/** Main loop when this class is in state 'WaitingForCoord0'. */
		void loop_WaitingForCoord0();
		/** Main loop when this class is in state 'WaitingForCoord1'. */
		void loop_WaitingForCoord1();
		/** Main loop when this class is in state 'WaitingForPlayer'. */
		void loop_WaitingForPlayer();
		/** Called when the user has requested the move for the given player. */
		void requestMove(Player player);
};

#endif
