#ifndef INCLUDE_SRC_COMMANDREADER_H
#define INCLUDE_SRC_COMMANDREADER_H

#include "Command.h"

/**
 * A class which provides user input.
 */
class CommandReader
{
	private:
		Command _command;
		Command _next_command;
		bool _want_toggle_god_mode;
		bool _next_want_toggle_god_mode;
		bool _god_mode_enabled;

	public:
		/**
		 * Initializes a new CommandReader instance.
		 */
		CommandReader();

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
		 * Indicates whether the god mode is currently enabled.
		 */
		bool isGodModeEnabled();

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
