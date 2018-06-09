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
#include "src/Controller.h"
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
TaskManager tasks;
// Inputs
BoolPinInput input_godmode(PIN_IN_GODMODE, true);
KeypadInput input_coord;
BoolPinInput input_playerA(PIN_IN_PLAYER_A, true);
BoolPinInput input_playerB(PIN_IN_PLAYER_B, true);
BoolPinInput input_playerX(PIN_IN_PLAYER_X, true);
// Outputs
BoolPinOutput output_playmode(PIN_OUT_PLAYMODE, true);
BoolPinOutput output_godmode(PIN_OUT_GODMODE, true);
BoolPinOutput output_playerA(PIN_OUT_PLAYER_A, true);
BoolPinOutput output_playerB(PIN_OUT_PLAYER_B, true);
BoolPinOutput output_playerX(PIN_OUT_PLAYER_X, true);
RgbwLedStripOutput output_tilecolors(BOARD_WIDTH * BOARD_HEIGHT, PIN_OUT_BOARD, FLAGS_NEOPIXEL);
// Controller
Controller controller(
	&input_coord,
	&input_playerA,
	&input_playerB,
	&input_playerX,
	&output_playerA,
	&output_playerB,
	&output_playerX,
	[&board, &game](Player player, Tile const& tile) { return game.playerCanMove(board, player, tile); },
	onPlayerMoveRequested);
// Globals
rgbw const color_playerA(COLOR_PLAYER_A);
rgbw const color_playerB(COLOR_PLAYER_B);
rgbw const color_playerX(COLOR_PLAYER_X);
// Local variables that require memory allocation
TileUpdate tileupdates_buffer[2 * BOARD_WIDTH * BOARD_HEIGHT]; // used in onPlayerMoveRequested()

void setup()
{
	// Initialize inputs and outputs
	input_godmode.setup();
	input_coord.setup();
	input_playerA.setup();
	input_playerB.setup();
	input_playerX.setup();
	output_playmode.setup();
	output_godmode.setup();
	output_playerA.setup();
	output_playerB.setup();
	output_playerX.setup();

	// Start the game
	game.beginRound();
}

void loop()
{
	// Update inputs
	input_godmode.update();
	input_coord.update();
	input_playerA.update();
	input_playerB.update();
	input_playerX.update();

	// Determine the game mode (normal or god mode)
	if (input_godmode.hasValueChanged())
	{
		bool is_godmode = input_godmode.getValue();

		// Set up game logic
		game = is_godmode ? (Game&)game_godmode : (Game&)game_default;

		// Reset state
		controller.reset();
		tasks.clear();
		syncTileLeds();

		// Turn on appropriate LED
		output_playmode.setValue(!is_godmode);
		output_godmode.setValue(is_godmode);
	}

	// Process user input
	// Possibly triggers onPlayerMoveRequested()
	controller.loop();

	// Run tasks
	tasks.loop();

	// Flush outputs
	output_playmode.flush();
	output_godmode.flush();
	output_playerA.flush();
	output_playerB.flush();
	output_playerX.flush();
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
		tasks.add(new BlinkTask(&output_playerA, ANIM_BLINK_TIME, ANIM_BLINK_NUM), 0, true);
		tasks.add(new BlinkTask(&output_playerB, ANIM_BLINK_TIME, ANIM_BLINK_NUM), 0, true);
		tasks.add(new BlinkTask(&output_playerX, ANIM_BLINK_TIME, ANIM_BLINK_NUM), 0, true);
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