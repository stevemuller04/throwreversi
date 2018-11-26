#include "src/Control/InputReader.h"
#include "src/Output/RgbwLedStripOutput.h"
#include "src/Engine.h"
#include "config.wiring.h"

InputReader input_reader;
RgbwLedStripOutput output_tilecolors(BOARD_WIDTH * BOARD_HEIGHT * 2, PIN_OUT_BOARD, FLAGS_NEOPIXEL);
Engine engine(input_reader, output_tilecolors, BOARD_WIDTH, BOARD_HEIGHT, LED_BUILTIN); 

void setup()
{
	output_tilecolors.setup();
	engine.setup();
}

void loop()
{
	input_reader.update();
	engine.loop();
	output_tilecolors.flush();
}
