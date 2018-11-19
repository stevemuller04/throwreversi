#include "src/Game/Board.h"
#include "src/Game/Game.h"
#include "src/Game/GodmodeGame.h"
#include "src/Game/DefaultGame.h"
#include "src/Task/TaskManager.h"
#include "src/types.h"
#include "src/Input/BoolPinInput.h"
#include "src/Input/KeypadInput.h"
#include "src/Output/BoolPinOutput.h"
#include "src/Output/RgbwLedStripOutput.h"
#include "src/Control/Command.h"
#include "src/Control/CommandReader.h"
#include "src/Game/TileUpdate.h"
#include "src/Task/RgbwFlashTask.h"
#include "src/Task/BlinkTask.h"
#include "config.h"

// Forward-declare all functions in this file
void setup();
void loop();
void onPlayerMoveRequested(Player player, Tile const &tile);
void syncTileLeds();

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
		is_godmode = !is_godmode;

		// Set up game logic
		game = is_godmode ? (Game&)game_godmode : (Game&)game_default;

		// Reset state
		controller.reset();
		tasks.clear();
		syncTileLeds();
	}

	// Process user input
	Command command = controller.read();
	if (command.has_changed && command.is_complete)
		onPlayerMoveRequested(command.selected_player, command.selected_tile);

	// Run tasks
	tasks.loop();

	// Flush outputs
	output_tilecolors.flush();
}

/**
 * Called when the user requested a player's move via the hardware interfaces.
 */
void onPlayerMoveRequested(Player player, Tile const &tile)
{
	// Make move
	int tileupdates_num;
	if (game.playerMove(board, player, tile, tileupdates_buffer, tileupdates_num))
	{
		// Show move animation
		tasks.clear();
		syncTileLeds();
		for (int i = 0; i < tileupdates_num; ++i)
		{
			Player const owner = tileupdates_buffer[i].owner;
			rgbw const color = owner == Player::PlayerA ? color_playerA : owner == Player::PlayerB ? color_playerB : color_playerX;
			ledId_t led_id = tileupdates_buffer[i].tile.y * board.getWidth() + tileupdates_buffer[i].tile.x;
			tasks.add(new RgbwFlashTask(&output_tilecolors, led_id, color, ANIM_FLASH_TIME, ANIM_FLASH_NUM), i * ANIM_FLASH_DELAY_PER_LED, true);
		}

		// Tell the Game instance that a new round begins
		game.beginRound();
	}
	else
	{
		// Show error animation
		tasks.clear();
		syncTileLeds();
	}
}

/**
 * Synchronizes the LEDs of the tiles with the current value in the GameBoard instance.
 * This method should be always called after an animation was aborted; which can
 * potentially always be the case when the TaskManager is cleared.
 */
void syncTileLeds()
{
	Tile tile;
	for (tile.x = 0; tile.x < board.getWidth(); ++tile.x)
	{
		for (tile.y = 0; tile.y < board.getHeight(); ++tile.y)
		{
			Player owner = board.getTileOwner(tile);
			output_tilecolors.setColor(
				tile.y * board.getWidth() + tile.x,
				owner == Player::PlayerA ? color_playerA : owner == Player::PlayerB ? color_playerB : color_playerX);
		}
	}
}