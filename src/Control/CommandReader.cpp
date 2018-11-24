#include "CommandReader.h"
#include "Command.h"

CommandReader::CommandReader(KeypadInput const *keypad_input) :
	_keypad_input(keypad_input),
	_command(Command::Empty)
{
}

void CommandReader::reset()
{
	_state = State::WaitingForCoord0;
	_command = Command();
}

Command CommandReader::update()
{
	// When ever the '*' key is pressed, the complete user input is discarded
	if (_keypad_input->hasNewValue() && _keypad_input->getValue() == '*')
	{
		_state = State::WaitingForCoord0;
		return _command = Command::Empty;
	}
	else
	{
		// Assume by default that the input did not change
		_command.has_changed = false;

		switch (_state)
		{
			case State::WaitingForCoord0:
				update_WaitingForCoord0();
				break;
			case State::WaitingForCoord1:
				update_WaitingForCoord1();
				break;
			case State::WaitingForPlayer:
				update_WaitingForPlayer();
				break;
		}

		return _command;
	}
}

void CommandReader::update_WaitingForCoord0()
{
	if (_keypad_input->hasNewValue() && _keypad_input->getValue() >= '1' && _keypad_input->getValue() <= '9')
	{
		_command.selected_tile.x = TILE_COORD_UNDETERMINED;
		_command.selected_tile.y = _keypad_input->getValue() - '1';
		_command.selected_player = Player::None;
		_command.has_changed = true;
		_command.is_complete = false;
		_state = State::WaitingForCoord1;
	}
}

void CommandReader::update_WaitingForCoord1()
{
	if (_keypad_input->hasNewValue() && _keypad_input->getValue() >= '1' && _keypad_input->getValue() <= '9')
	{
		_command.selected_tile.x = _keypad_input->getValue() - '1';
		_command.selected_player = Player::None;
		_command.has_changed = true;
		_command.is_complete = false;
		_state = State::WaitingForPlayer;
	}
}

void CommandReader::update_WaitingForPlayer()
{
	if (_keypad_input->hasNewValue())
	{
		switch (_keypad_input->getValue())
		{
			case 'A':
				tryRequestMove(Player::PlayerA);
				break;
			case 'B':
				tryRequestMove(Player::PlayerB);
				break;
			case 'C':
			case 'D':
				tryRequestMove(Player::None);
				break;
		}
	}
}

void CommandReader::tryRequestMove(Player player)
{
	_state = State::WaitingForCoord0;
	_command.selected_player = player;
	_command.has_changed = true;
	_command.is_complete = true;
}
