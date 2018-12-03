#ifndef INCLUDE_SRC_CONTROLSERVER_H
#define INCLUDE_SRC_CONTROLSERVER_H

#include "CommandReader.h"
#include "../Game/Board.h"
#include <ESP8266WebServer.h>

/**
 * A web server that allows to control the game.
 */
class ControlServer
{
	private:
		CommandReader &_command_reader;
		Board const &_board;
		ESP8266WebServer _server;

	public:
		/**
		 * Initializes a new ControlServer instance.
		 */
		ControlServer(CommandReader &command_reader, Board const &board);

		/**
		 * Sets up the web server.
		 * @param html A PROGMEM pointer to the HTML source code of the main application.
		 */
		void setup(PGM_P html);

		/**
		 * Main loop that handles web clients and their requests.
		 */
		void loop();

	private:
		/**
		 * Handles requests to the '/' URI.
		 * Provides the web interface to wbe clients.
		 * @param html The HTML source code that shall be returned to clients.
		 */
		void handleRoot(PGM_P html);

		/**
		 * Handles requests to the '/godmode' URI.
		 * Toggles the god mode.
		 */
		void handleGodMode();

		/**
		 * Handles requests to the '/move' URI.
		 * Plays a move.
		 */
		void handleMove();

		/**
		 * Handles requests to the '/board' URI.
		 * Provides a JSON representation of the game state to wbe clients.
		 */
		void handleBoard();
};

#endif
