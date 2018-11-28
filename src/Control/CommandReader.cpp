#include "CommandReader.h"

CommandReader::CommandReader()
{
	_next_want_toggle_god_mode = false;
	_next_command.has_changed = false;
	_god_mode_enabled = false;
}

void CommandReader::toggleGodMode()
{
	_next_want_toggle_god_mode = true;
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
	return _want_toggle_god_mode;
}

bool CommandReader::isGodModeEnabled()
{
	return _god_mode_enabled;
}

void CommandReader::update()
{
	_command = _next_command;
	_want_toggle_god_mode = _next_want_toggle_god_mode;

	_next_command.has_changed = false;
	_next_want_toggle_god_mode = false;

	if (_want_toggle_god_mode)
		_god_mode_enabled = !_god_mode_enabled;
}
