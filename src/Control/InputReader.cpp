#include "InputReader.h"

InputReader::InputReader()
{
	_next_want_god_mode = false;
	_next_command.has_changed = false;
}

void InputReader::toggleGodMode()
{
	_next_want_god_mode = true;
}

void InputReader::setCommand(Command command)
{
	_next_command = command;
}

Command InputReader::getCommand()
{
	return _command;
}

bool InputReader::wantGodModeToggle()
{
	return _want_god_mode;
}

void InputReader::update()
{
	_command = _next_command;
	_want_god_mode = _next_want_god_mode;

	_next_command.has_changed = false;
	_want_god_mode = false;
}
