#include "CommandReader.h"

CommandReader::CommandReader()
{
	_next_want_god_mode = false;
	_next_command.has_changed = false;
}

void CommandReader::toggleGodMode()
{
	_next_want_god_mode = true;
}

void CommandReader::setCommand(Command command)
{
	_next_command = command;
}

Command CommandReader::getCommand()
{
	return _command;
}

bool CommandReader::wantGodModeToggle()
{
	return _want_god_mode;
}

void CommandReader::update()
{
	_command = _next_command;
	_want_god_mode = _next_want_god_mode;

	_next_command.has_changed = false;
	_want_god_mode = false;
}
