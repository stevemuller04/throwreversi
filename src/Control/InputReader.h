#ifndef INCLUDE_SRC_INPUTREADER_H
#define INCLUDE_SRC_INPUTREADER_H

#include "Command.h"

/**
 * A class which provides user input.
 */
class InputReader
{
	private:
		Command _command;
		Command _next_command;
		bool _want_god_mode;
		bool _next_want_god_mode;

	public:
		/**
		 * Initializes a new InputReader instance.
		 */
		InputReader();

		/**
		 * Gets the command set via setCommand().
		 */
		Command getCommand();

		/**
		 * Indicates whether the toggling of the god mode has been requested.
		 */
		bool wantGodModeToggle();

		/**
		 * Toggles the god mode.
		 */
		void toggleGodMode();

		/**
		 * Sets the next command.
		 */
		void setCommand(Command command);

		/**
		 * Applies the requested user commands.
		 * Must be called at the beginning of each loop.
		 */
		void update();
};

#endif
