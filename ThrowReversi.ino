#include "src/Control/CommandReader.h"
#include "src/Control/ControlServer.h"
#include "src/Output/RgbwLedStripOutput.h"
#include "src/Engine.h"
#include "config.wiring.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

CommandReader command_reader;
RgbwLedStripOutput output_tilecolors(BOARD_WIDTH * BOARD_HEIGHT * 2, PIN_OUT_BOARD, FLAGS_NEOPIXEL);
Engine engine(command_reader, output_tilecolors, BOARD_WIDTH, BOARD_HEIGHT, LED_BUILTIN); 
ControlServer control_server(command_reader, engine.getBoard());

const char HTML[] =
#include "HTML.h"
;

void setup()
{
	delay(1000);
	engine.setup();
	output_tilecolors.setup();
	control_server.setup(HTML);

	WiFi.softAP("ThrowReversi");
}

void loop()
{
	control_server.loop();
	command_reader.update();
	engine.loop();
	output_tilecolors.flush();
}
