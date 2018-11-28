#include "ControlServer.h"
#include "Command.h"

ControlServer::ControlServer(CommandReader &command_reader) :
	_command_reader(command_reader),
	_server(80)
{
}

void ControlServer::setup()
{
	_server.on("/", [this] () { return this->handleRoot(); });
	_server.begin();
}

void ControlServer::loop()
{
	_server.handleClient();
}

void ControlServer::handleRoot()
{
	_server.send(200, "text/html", "<html><body><h1>ThrowReversi</h1></body></html>");
}
