#include "Engine.h"
#include "Task/RgbwaFlashTask.h"
#include "types.h"
#include "../config.visual.h"

rgbw const Engine::_color_playerA(COLOR_PLAYER_A);
rgbw const Engine::_color_playerB(COLOR_PLAYER_B);
rgbw const Engine::_color_playerX(COLOR_PLAYER_X);

Engine::Engine(InputReader &input_reader, RgbwLedStripOutput &output_tilecolors, coord_t width, coord_t height, uint8_t godmode_pin) :
	_width(width),
	_height(height),
	_is_godmode(false),
	_godmode_pin(godmode_pin),
	_output_tilecolors(output_tilecolors),
	_input_reader(input_reader),
	_output_manager(LedMatrixOutputManager(width, height, output_tilecolors)),
	_board(Board(width, height)),
	_tileupdates_buffer(new TileUpdate[2 * width * height])
{
	_game = &_game_default;
}

Engine::~Engine()
{
	delete[] _tileupdates_buffer;
}

void Engine::setup()
{
	_game->beginRound();
}

void Engine::loop()
{
	handleInput();

	// Run animations
	_tasks.loop();

	// Flush outputs
	_output_manager.flush();
}

void Engine::handleInput()
{
	// Handle game mode toggling (normal or god mode)
	if (_input_reader.wantGodModeToggle())
	{
		handleInput_GodMode();
	}
	else
	{
		// Process user input
		Command command = _input_reader.getCommand();
		if (command.has_changed)
		{
			// Stop animations after user input
			stopAnimations();

			// If all parts of the user input have been specified, and the move is legal, handle the request
			if (command.is_complete && _game->playerCanMove(_board, command.selected_player, command.selected_tile))
			{
				handleInput_Command(command.selected_player, command.selected_tile);
			}
		}
	}
}

void Engine::handleInput_GodMode()
{
	// Toggle flag
	_is_godmode = !_is_godmode;

	// Set up game logic
	_game = _is_godmode ? (Game*)&_game_godmode : (Game*)&_game_default;

	// Reset state and stop animations
	stopAnimations();

	// Show god mode animation
	rgbwa color_overlay(0, 0, 0, 0, ANIM_GODMODE_FLASH_ALPHA);
	for (coord_t x = 0; x < _width; ++x)
		for (coord_t y = 0; y < _height; ++y)
			_tasks.add(new RgbwaFlashTask(_output_manager, x, y, color_overlay, rgbwa::transparent, ANIM_GODMODE_FLASH_TIME, ANIM_GODMODE_FLASH_NUM), 0, true);
}

void Engine::handleInput_Command(Player player, Tile tile)
{
	// Make move
	int tileupdates_num;
	if (_game->playerMove(_board, player, tile, _tileupdates_buffer, tileupdates_num))
	{
		// Visualise move
		for (int i = 0; i < tileupdates_num; ++i)
		{
			// Set new base color for the tile
			Tile const tile = _tileupdates_buffer[i].tile;
			Player const owner = _tileupdates_buffer[i].owner;
			rgbw const color = getPlayerColor(owner);
			_output_manager.setBaseColor(tile.x, tile.y, color);

			// Add animation
			_tasks.add(new RgbwaFlashTask(_output_manager, tile.x, tile.y, getPlayerColor(_tileupdates_buffer[i].previous_owner), color, ANIM_CONQUER_FLASH_TIME, ANIM_CONQUER_FLASH_NUM), 0, true);
		}

		// Tell the Game instance that a new round begins
		_game->beginRound();
	}
}

void Engine::stopAnimations()
{
	// Stop the animations
	_tasks.clear();

	// Reset the overlays
	for (coord_t x = 0; x < _width; ++x)
		for (coord_t y = 0; y < _height; ++y)
			_output_manager.setOverlayColor(x, y, rgbwa::transparent);
}

rgbw Engine::getPlayerColor(Player player)
{
	switch (player)
	{
		case Player::PlayerA: return _color_playerA;
		case Player::PlayerB: return _color_playerB;
		default: return _color_playerX;
	}
}
