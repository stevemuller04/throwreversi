#ifndef INCLUDE_SRC_CONTROLSERVER_H
#define INCLUDE_SRC_CONTROLSERVER_H

#include "InputReader.h"
#include <ESP8266WebServer.h>

/**
 * A web server that allows to control the game.
 */
class ControlServer
{
	private:
		InputReader _input_reader;
		ESP8266WebServer _server;

	public:
		/**
		 * Initializes a new ControlServer instance.
		 */
		ControlServer(InputReader &input_reader);

		/**
		 * Sets up the web server.
		 */
		void setup();

		/**
		 * Main loop that handles web clients and their requests.
		 */
		void loop();

	private:
		void handleRoot();
};

#endif
