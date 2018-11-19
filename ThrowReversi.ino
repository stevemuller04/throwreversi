#include "src/Game/Board.h"
#include "src/Game/Game.h"
#include "src/Game/GodmodeGame.h"
#include "src/Game/DefaultGame.h"
#include "src/Task/TaskManager.h"
#include "src/types.h"
#include "src/Input/KeypadInput.h"
#include "src/Output/RgbwLedStripOutput.h"
#include "src/Control/Command.h"
#include "src/Control/CommandReader.h"
#include "src/Control/LedMatrixOutputManager.h"
#include "src/Game/TileUpdate.h"
#include "config.h"

// Forward-declare all functions in this file
void setup();
void loop();
void onGodModeToggled();
void onPlayerMoveRequested(Player player, Tile const &tile);

// Model
Board board(BOARD_WIDTH, BOARD_HEIGHT);
DefaultGame game_default;
GodmodeGame game_godmode;
Game& game = game_default;
bool is_godmode = false;
TaskManager tasks;
// Hardware
KeypadInput input_keypad(PIN_IN_KEYPAD_ROW0, PIN_IN_KEYPAD_ROW1, PIN_IN_KEYPAD_ROW2, PIN_IN_KEYPAD_ROW3, PIN_IN_KEYPAD_COL0, PIN_IN_KEYPAD_COL1, PIN_IN_KEYPAD_COL2);
RgbwLedStripOutput output_tilecolors(BOARD_WIDTH * BOARD_HEIGHT, PIN_OUT_BOARD, FLAGS_NEOPIXEL);
// Control
CommandReader controller(
	&input_keypad,
	[&board, &game](Player player, Tile const& tile) { return game.playerCanMove(board, player, tile); });
LedMatrixOutputManager matrix(BOARD_WIDTH, BOARD_HEIGHT, &output_tilecolors);
// Globals
rgbw const color_playerA(COLOR_PLAYER_A);
rgbw const color_playerB(COLOR_PLAYER_B);
rgbw const color_playerX(COLOR_PLAYER_X);
// Local variables that require memory allocation
TileUpdate tileupdates_buffer[2 * BOARD_WIDTH * BOARD_HEIGHT]; // used in onPlayerMoveRequested()

void setup()
{
	// Initialize inputs and outputs
	input_keypad.setup();
	output_tilecolors.setup();

	// Start the game
	game.beginRound();
}

void loop()
{
	// Update inputs
	input_keypad.update();

	// Determine the game mode (normal or god mode)
	if (input_keypad.hasNewValue() && input_keypad.getValue() == '#')
	{
		onGodModeToggled();
	}

	// Process user input
	Command command = controller.read();
	if (command.has_changed && command.is_complete)
	{
		onPlayerMoveRequested(command.selected_player, command.selected_tile);
	}

	// Run tasks
	tasks.loop();

	// Flush outputs
	output_tilecolors.flush();
}

/**
 * Called when the user requested entering/leaving the god mode.
 */
void onGodModeToggled()
{
	// Toggle flag
	is_godmode = !is_godmode;

	// Set up game logic
	game = is_godmode ? (Game&)game_godmode : (Game&)game_default;

	// Reset state
	controller.reset();
	tasks.clear();
}

/**
 * Called when the user requested a player's move.
 */
void onPlayerMoveRequested(Player player, Tile const &tile)
{
	// Make move
	int tileupdates_num;
	if (game.playerMove(board, player, tile, tileupdates_buffer, tileupdates_num))
	{
		// Show move animation
		tasks.clear();
		for (int i = 0; i < tileupdates_num; ++i)
		{
			Player const owner = tileupdates_buffer[i].owner;
			rgbw const color = owner == Player::PlayerA ? color_playerA : owner == Player::PlayerB ? color_playerB : color_playerX;
			matrix.setBaseColor(tileupdates_buffer[i].tile.x, tileupdates_buffer[i].tile.y, color);
		}

		// Tell the Game instance that a new round begins
		game.beginRound();
	}
	else
	{
		// Show error animation
		tasks.clear();
	}
}
