#include "Engine.h"
#include "Task/RgbwaFlashTask.h"
#include "types.h"
#include "../config.h"

rgbw const Engine::color_playerA(COLOR_PLAYER_A);
rgbw const Engine::color_playerB(COLOR_PLAYER_B);
rgbw const Engine::color_playerX(COLOR_PLAYER_X);

Engine::Engine(KeypadInput &input_keypad, RgbwLedStripOutput &output_tilecolors, coord_t width, coord_t height, uint8_t godmode_pin) :
	width(width),
	height(height),
	is_godmode(false),
	godmode_pin(godmode_pin),
	input_keypad(input_keypad),
	output_tilecolors(output_tilecolors),
	command_reader(CommandReader(&input_keypad)),
	output_manager(LedMatrixOutputManager(width, height, &output_tilecolors)),
	board(Board(width, height))
{
	game = &game_default;
	tileupdates_buffer = new TileUpdate[2 * width * height];
}

Engine::~Engine()
{
	delete[] tileupdates_buffer;
}

Engine::setup()
{
	pinMode(godmode_pin, OUTPUT);
	digitalWrite(godmode_pin, LOW);

	game->beginRound();
}

Engine::loop()
{
	handleInput();

	// Run animations
	tasks.loop();

	// Flush outputs
	output_manager.flush();
}

Engine::handleInput()
{
	// Handle game mode toggling (normal or god mode)
	if (input_keypad.hasNewValue() && input_keypad.getValue() == '#')
	{
		handleInput_GodMode();
	}
	else
	{
		// Process user input
		Command command = command_reader.update();
		if (command.has_changed)
		{
			// Stop animations after user input
			stopAnimations();

			// If all parts of the user input have been specified, and the move is legal, handle the request
			if (command.is_complete && game->playerCanMove(board, command.selected_player, command.selected_tile))
			{
				handleInput_Command(command.selected_player, command.selected_tile);
			}
		}
	}
}

Engine::handleInput_GodMode()
{
	// Toggle flag
	is_godmode = !is_godmode;
	digitalWrite(godmode_pin, is_godmode ? HIGH : LOW);

	// Set up game logic
	game = is_godmode ? (Game*)&game_godmode : (Game*)&game_default;

	// Reset state and stop animations
	command_reader.reset();
	stopAnimations();

	// Show god mode animation
	rgbwa color_overlay(0, 0, 0, 0, ANIM_FLASH_ALPHA);
	for (coord_t x = 0; x < width; ++x)
		for (coord_t y = 0; y < height; ++y)
			tasks.add(new RgbwaFlashTask(&output_manager, x, y, color_overlay, ANIM_FLASH_TIME, ANIM_FLASH_NUM), 0, true);
}

Engine::handleInput_Command(Player player, Tile tile)
{
	// Make move
	int tileupdates_num;
	if (game->playerMove(board, player, tile, tileupdates_buffer, tileupdates_num))
	{
		// Visualise move
		for (int i = 0; i < tileupdates_num; ++i)
		{
			// Set new base color for the tile
			Player const owner = tileupdates_buffer[i].owner;
			rgbw const color = owner == Player::PlayerA ? color_playerA : owner == Player::PlayerB ? color_playerB : color_playerX;
			output_manager.setBaseColor(tileupdates_buffer[i].tile.x, tileupdates_buffer[i].tile.y, color);
		}

		// Tell the Game instance that a new round begins
		game->beginRound();
	}
}

Engine::stopAnimations()
{
	tasks.clear();
}
