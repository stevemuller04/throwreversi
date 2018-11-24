#include "src/Input/KeypadInput.h"
#include "src/Output/RgbwLedStripOutput.h"
#include "src/Engine.h"
#include "config.wiring.h"

KeypadInput input_keypad(PIN_IN_KEYPAD_ROW0, PIN_IN_KEYPAD_ROW1, PIN_IN_KEYPAD_ROW2, PIN_IN_KEYPAD_ROW3, PIN_IN_KEYPAD_COL0, PIN_IN_KEYPAD_COL1, PIN_IN_KEYPAD_COL2, PIN_IN_KEYPAD_COL3);
RgbwLedStripOutput output_tilecolors(BOARD_WIDTH * BOARD_HEIGHT * 2, PIN_OUT_BOARD, FLAGS_NEOPIXEL);
Engine engine(input_keypad, output_tilecolors, BOARD_WIDTH, BOARD_HEIGHT, LED_BUILTIN); 

void setup()
{
	input_keypad.setup();
	output_tilecolors.setup();
	engine.setup();
}

void loop()
{
	input_keypad.update();
	engine.loop();
	output_tilecolors.flush();
}
