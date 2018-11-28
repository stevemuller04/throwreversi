#include "src/Control/CommandReader.h"
#include "src/Control/ControlServer.h"
#include "src/Output/RgbwLedOutput.h"
#include "src/Output/RgbwLedStripOutput.h"
#include "src/Engine.h"
#include "config.wiring.h"
#include "config.visual.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

RgbwLedOutput status_led(STATUSLED_PIN, STATUSLED_FLAGS);
CommandReader command_reader;
RgbwLedStripOutput output_tilecolors(BOARD_WIDTH * BOARD_HEIGHT * 2, BOARDLEDS_PIN, BOARDLEDS_FLAGS);
Engine engine(command_reader, output_tilecolors, BOARD_WIDTH, BOARD_HEIGHT, LED_BUILTIN); 
ControlServer control_server(command_reader, engine.getBoard());

const char HTML[] =
#include "HTML.h"
;

void setup()
{
	// LED to show "loading" status
	status_led.setup();
	status_led.setColor(rgbw(COLOR_STATUS_LOAD));
	status_led.flush();
	delay(1000);

	// Set up components
	engine.setup();
	output_tilecolors.setup();
	control_server.setup(HTML);

	// Set up WiFi access point
	WiFi.softAP("ThrowReversi");

	// LED to show "done" status
	status_led.setColor(rgbw(COLOR_STATUS_DONE));
	status_led.flush();
}

void loop()
{
	control_server.loop();
	command_reader.update();
	engine.loop();
	output_tilecolors.flush();
}
