#ifndef INCLUDE_SRC_ENGINE_H
#define INCLUDE_SRC_ENGINE_H

#include "Input/KeypadInput.h"
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

class Engine
{
	private:
		coord_t width;
		coord_t height;
		bool is_godmode;
		uint8_t godmode_pin;
		KeypadInput input_keypad;
		RgbwLedStripOutput output_tilecolors;
		CommandReader command_reader;
		LedMatrixOutputManager output_manager;
		Board board;
		Game *game;
		DefaultGame game_default;
		GodmodeGame game_godmode;
		TileUpdate *tileupdates_buffer; // used as buffer in handleInput_Command()
		TaskManager tasks;

		static rgbw const color_playerA;
		static rgbw const color_playerB;
		static rgbw const color_playerX;

	public:
		Engine(KeypadInput &input_keypad, RgbwLedStripOutput &output_tilecolors, coord_t width, coord_t height, uint8_t godmode_pin);
		~Engine();
		void setup();
		void loop();

	private:
		void handleInput();
		void handleInput_GodMode();
		void handleInput_Command(Player player, Tile tile);
		void stopAnimations();
		rgbw getPlayerColor(Player player);
};

#endif
