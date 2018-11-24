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
		coord_t const _width;
		coord_t const _height;
		bool _is_godmode;
		uint8_t _godmode_pin;
		KeypadInput &_input_keypad;
		RgbwLedStripOutput &_output_tilecolors;
		CommandReader _command_reader;
		LedMatrixOutputManager _output_manager;
		Board _board;
		Game *_game;
		DefaultGame _game_default;
		GodmodeGame _game_godmode;
		TileUpdate * const _tileupdates_buffer; // used as buffer in handleInput_Command()
		TaskManager _tasks;

		static rgbw const _color_playerA;
		static rgbw const _color_playerB;
		static rgbw const _color_playerX;

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
