#include "src/Control/InputReader.h"
#include "src/Control/ControlServer.h"
#include "src/Output/RgbwLedStripOutput.h"
#include "src/Engine.h"
#include "config.wiring.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

InputReader input_reader;
ControlServer control_server(input_reader);
RgbwLedStripOutput output_tilecolors(BOARD_WIDTH * BOARD_HEIGHT * 2, PIN_OUT_BOARD, FLAGS_NEOPIXEL);
Engine engine(input_reader, output_tilecolors, BOARD_WIDTH, BOARD_HEIGHT, LED_BUILTIN); 

void setup()
{
	delay(1000);
	engine.setup();
	output_tilecolors.setup();
	control_server.setup();

	WiFi.softAP("ThrowReversi");
}

void loop()
{
	control_server.loop();
	input_reader.update();
	engine.loop();
	output_tilecolors.flush();
}
