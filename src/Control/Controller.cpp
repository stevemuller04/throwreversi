#include "Controller.h"
#include "UserInput.h"

Controller::Controller(
	KeypadInput const *keypad_input,
	BoolPinInput const *playerA_input,
	BoolPinInput const *playerB_input,
	BoolPinInput const *playerX_input,
	BoolPinOutput *playerA_output,
	BoolPinOutput *playerB_output,
	BoolPinOutput *playerX_output,
	bool (*player_can_move_callback)(Player, Tile const&)) :
	_keypad_input(keypad_input),
	_playerA_input(playerA_input),
	_playerB_input(playerB_input),
	_playerX_input(playerX_input),
	_playerA_output(playerA_output),
	_playerB_output(playerB_output),
	_playerX_output(playerX_output),
	_player_can_move_callback(player_can_move_callback),
	_input()
{
}

void Controller::reset()
{
	_state = State::WaitingForCoord0;
	_input = UserInput();
	_playerA_output->setValue(false);
	_playerB_output->setValue(false);
	_playerX_output->setValue(false);
}

UserInput Controller::loop()
{
	// Special case: when ever the '#' or '*' key is pressed, the complete user input is discarded
	if (_keypad_input->hasNewValue() && (_keypad_input->getValue() == '#' || _keypad_input->getValue() == '*'))
	{
		_state = State::WaitingForCoord0;
		_input = UserInput();
		return _input; // we won't read a coordinate in loop_WaitingForCoord0() anyway, so abort completely
	}

	_input.has_changed = false; // unless one of the functions below change something

	switch (_state)
	{
		case State::WaitingForCoord0:
			loop_WaitingForCoord0();
			break;
		case State::WaitingForCoord1:
			loop_WaitingForCoord1();
			break;
		case State::WaitingForPlayer:
			loop_WaitingForPlayer();
			break;
	}

	return _input;
}

void Controller::loop_WaitingForCoord0()
{
	if (_keypad_input->hasNewValue() && _keypad_input->getValue() >= '1' && _keypad_input->getValue() <= '9')
	{
		_input.selected_tile.x = _keypad_input->getValue() - '1';
		_input.has_changed = true;
		_state = State::WaitingForCoord1;
	}
}

void Controller::loop_WaitingForCoord1()
{
	if (_keypad_input->hasNewValue() && _keypad_input->getValue() >= '1' && _keypad_input->getValue() <= '9')
	{
		_input.selected_tile.y = _keypad_input->getValue() - '1';
		_input.has_changed = true;
		_state = State::WaitingForPlayer;

		_playerA_output->setValue(_player_can_move_callback(Player::PlayerA, _input.selected_tile));
		_playerB_output->setValue(_player_can_move_callback(Player::PlayerB, _input.selected_tile));
		_playerX_output->setValue(_player_can_move_callback(Player::None, _input.selected_tile));
	}
}

void Controller::loop_WaitingForPlayer()
{
	if (_playerA_input->hasValueChanged() && _playerA_input->getValue() && _player_can_move_callback(Player::PlayerA, _input.selected_tile))
	{
		requestMove(Player::PlayerA);
	}
	else if (_playerB_input->hasValueChanged() && _playerB_input->getValue() && _player_can_move_callback(Player::PlayerB, _input.selected_tile))
	{
		requestMove(Player::PlayerB);
	}
	else if (_playerX_input->hasValueChanged() && _playerX_input->getValue() && _player_can_move_callback(Player::None, _input.selected_tile))
	{
		requestMove(Player::None);
	}
}

void Controller::requestMove(Player player)
{
	_playerA_output->setValue(false);
	_playerB_output->setValue(false);
	_playerX_output->setValue(false);

	_state = State::WaitingForCoord0;
	_input.selected_player = player;
	_input.has_changed = true;
	_input.is_complete = true;
}