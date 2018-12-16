#include "ControlServer.h"
#include "Command.h"
#include "../Game/Tile.h"
#include "../Game/Player.h"
#include "../types.h"

static const char ControlServer_contenttype[] PROGMEM = "text/html";

ControlServer::ControlServer(CommandReader &command_reader, Board const &board) :
	_command_reader(command_reader),
	_board(board),
	_server(80)
{
}

void ControlServer::setup(PGM_P html)
{
	_server.on("/", HTTP_GET, [this, html] () { return this->handleRoot(html); });
	_server.on("/godmode", HTTP_POST, [this] () { return this->handleGodMode(); });
	_server.on("/move", HTTP_POST, [this] () { return this->handleMove(); });
	_server.on("/reset", HTTP_POST, [this] () { return this->handleReset(); });
	_server.on("/board", HTTP_GET, [this] () { return this->handleBoard(); });
	_server.begin();
}

void ControlServer::loop()
{
	_server.handleClient();
}

void ControlServer::handleRoot(PGM_P html)
{
	_server.send_P(200, ControlServer_contenttype, html);
}

void ControlServer::handleGodMode()
{
	_command_reader.toggleGodMode();
	_server.send(200, "text/json", "{}");
}

void ControlServer::handleMove()
{
	// Check if required parameters exist
	if (!_server.hasArg("x") || !_server.hasArg("y") || !_server.hasArg("p"))
	{
		_server.send(400, "text/json", "{\"error\":\"Missing x/y/p parameters\"}");
		return;
	}

	// Parse parameters and ensure that they are in the right range
	Tile tile;
	tile.x = _server.arg("x").toInt();
	tile.y = _server.arg("y").toInt();
	if (!_board.contains(tile))
	{
		_server.send(400, "text/json", "{\"error\":\"(x,y) out of board\"}");
		return;
	}
	int player_int = _server.arg("p").toInt();
	Player player;
	switch (player_int)
	{
		case 0: player = Player::None; break;
		case 1: player = Player::PlayerA; break;
		case 2: player = Player::PlayerB; break;
		default:
			_server.send(400, "text/json", "{\"error\":\"Bad player\"}");
			return;
	}

	// Set command
	Command command;
	command.selected_tile = tile;
	command.selected_player = player;
	command.has_changed = true;
	command.is_complete = true;
	_command_reader.setCommand(command);

	// Send OK
	_server.send(200, "text/json", "{}");
}

void ControlServer::handleReset()
{
	_command_reader.triggerReset();
	_server.send(200, "text/json", "{}");
}

void ControlServer::handleBoard()
{
	String msg = "{\"godmode\":";
	if (_command_reader.isGodModeEnabled())
		msg += "true";
	else
		msg += "false";
	msg += ",\"board\":[";
	Tile tile;
	for (tile.y = 0; tile.y < _board.getHeight(); ++tile.y)
	{
		if (tile.y > 0) msg += ",";
		msg += "[";
		for (tile.x = 0; tile.x < _board.getWidth(); ++tile.x)
		{
			if (tile.x > 0) msg += ",";
			switch (_board.getTileOwner(tile))
			{
				case Player::PlayerA: msg += "1"; break;
				case Player::PlayerB: msg += "2"; break;
				default: msg += "0"; break;
			}
		}
		msg += "]";
	}
	msg += "]}";
	_server.send(200, "text/json", msg);
}
