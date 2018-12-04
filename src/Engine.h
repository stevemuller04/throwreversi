#ifndef INCLUDE_SRC_ENGINE_H
#define INCLUDE_SRC_ENGINE_H

#include "Output/RgbwLedStripOutput.h"
#include "Control/Command.h"
#include "Control/CommandReader.h"
#include "Control/LedMatrixOutputManager.h"
#include "Game/Board.h"
#include "Game/Game.h"
#include "Game/DefaultGame.h"
#include "Game/GodmodeGame.h"
#include "Game/Player.h"
#include "Game/Tile.h"
#include "Game/TileUpdate.h"
#include "Task/TaskManager.h"
#include "types.h"

#define ENGINE_LAYER_COMMAND 1
#define ENGINE_LAYER_GODMODE 2

class Engine
{
	private:
		coord_t const _width;
		coord_t const _height;
		bool _is_godmode;
		uint8_t _godmode_pin;
		RgbwLedStripOutput &_output_tilecolors;
		CommandReader &_command_reader;
		LedMatrixOutputManager _output_manager;
		Board _board;
		Game *_game;
		DefaultGame _game_default;
		GodmodeGame _game_godmode;
		TileUpdate * const _tileupdates_buffer; // used as buffer in handleInput_Command()
		TaskManager _animations_command; // tasks for animations related to commands
		TaskManager _animations_godmode; // tasks for animations related to godmode changes

		static rgbw const _color_playerA;
		static rgbw const _color_playerB;
		static rgbw const _color_playerX;

	public:
		/**
		 * Initializes a new Engine.
		 * @param command_reader A command reader which retrieves user input.
		 * @param output_tilecolors An LED strip that visualises the game board.
		 * @param width The board width.
		 * @param height The board height.
		 */
		Engine(CommandReader &command_reader, RgbwLedStripOutput &output_tilecolors, coord_t width, coord_t height);

		/**
		 * Destroys the engine and frees all resources.
		 */
		~Engine();

		/**
		 * Sets up the engine and creates the necessary resources.
		 * To be called in the main setup() function.
		 */
		void setup();

		/**
		 * Executes the main logic of the engine.
		 * To be called in the main loop() function.
		 */
		void loop();

		/**
		 * Gets the current state of the game board.
		 */
		Board &getBoard();

	private:
		/**
		 * Process user input.
		 */
		void handleInput();

		/**
		 * Process the 'godmode toggling' part of the user input.
		 */
		void handleInput_GodMode();

		/**
		 * Process the 'move command' part of the user input.
		 * @param player The player that requests the move.
		 * @param tile The tile that is requested by the player for the move.
		 */
		void handleInput_Command(Player player, Tile tile);

		/**
		 * Stops all animations related to commands.
		 */
		void stopAnimations_Command();

		/**
		 * Stops all animations related to godmode changes.
		 */
		void stopAnimations_GodMode();

		/**
		 * Gets the color associated to the given player.
		 * @param player The player.
		 */
		rgbw getPlayerColor(Player player);
};

#endif
