#include "Engine.h"
#include "Task/RgbwaFlashTask.h"
#include "types.h"
#include "../config.visual.h"

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
	command_reader(CommandReader(input_keypad)),
	output_manager(LedMatrixOutputManager(width, height, output_tilecolors)),
	board(Board(width, height)),
	tileupdates_buffer(new TileUpdate[2 * width * height])
{
	game = &game_default;
}

Engine::~Engine()
{
	delete[] tileupdates_buffer;
}

void Engine::setup()
{
	pinMode(godmode_pin, OUTPUT);
	digitalWrite(godmode_pin, LOW);

	game->beginRound();
}

void Engine::loop()
{
	handleInput();

	// Run animations
	tasks.loop();

	// Flush outputs
	output_manager.flush();
}

void Engine::handleInput()
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

void Engine::handleInput_GodMode()
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
	rgbwa color_overlay(0, 0, 0, 0, ANIM_GODMODE_FLASH_ALPHA);
	for (coord_t x = 0; x < width; ++x)
		for (coord_t y = 0; y < height; ++y)
			tasks.add(new RgbwaFlashTask(output_manager, x, y, color_overlay, rgbwa::transparent, ANIM_GODMODE_FLASH_TIME, ANIM_GODMODE_FLASH_NUM), 0, true);
}

void Engine::handleInput_Command(Player player, Tile tile)
{
	// Make move
	int tileupdates_num;
	if (game->playerMove(board, player, tile, tileupdates_buffer, tileupdates_num))
	{
		// Visualise move
		for (int i = 0; i < tileupdates_num; ++i)
		{
			// Set new base color for the tile
			Tile const tile = tileupdates_buffer[i].tile;
			Player const owner = tileupdates_buffer[i].owner;
			rgbw const color = getPlayerColor(owner);
			output_manager.setBaseColor(tile.x, tile.y, color);

			// Add animation
			tasks.add(new RgbwaFlashTask(output_manager, tile.x, tile.y, getPlayerColor(tileupdates_buffer[i].previous_owner), color, ANIM_CONQUER_FLASH_TIME, ANIM_CONQUER_FLASH_NUM), 0, true);
		}

		// Tell the Game instance that a new round begins
		game->beginRound();
	}
}

void Engine::stopAnimations()
{
	// Stop the animations
	tasks.clear();

	// Reset the overlays
	for (coord_t x = 0; x < width; ++x)
		for (coord_t y = 0; y < height; ++y)
			output_manager.setOverlayColor(x, y, rgbwa::transparent);
}

rgbw Engine::getPlayerColor(Player player)
{
	switch (player)
	{
		case Player::PlayerA: return color_playerA;
		case Player::PlayerB: return color_playerB;
		default: return color_playerX;
	}
}
