#include "src/Control/CommandReader.h"
#include "src/Control/ControlServer.h"
#include "src/Output/RgbwLedOutput.h"
#include "src/Output/RgbwLedStripOutput.h"
#include "src/Engine.h"
#include "config.wiring.h"
#include "config.visual.h"
#include "config.net.h"
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>

RgbwLedOutput status_led(STATUSLED_PIN, STATUSLED_FLAGS);
CommandReader command_reader;
RgbwLedStripOutput output_tilecolors(BOARD_WIDTH * BOARD_HEIGHT * 2, BOARDLEDS_PIN, BOARDLEDS_FLAGS);
Engine engine(command_reader, output_tilecolors, BOARD_WIDTH, BOARD_HEIGHT); 
ControlServer control_server(command_reader, engine.getBoard());

IPAddress local_ip(NET_LOCAL_IP);
IPAddress local_ip_mask(NET_LOCAL_IP_MASK);
DNSServer dnsServer;

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
	if (!WiFi.mode(WIFI_AP)) fail();
	if (!WiFi.softAPConfig(local_ip, local_ip, local_ip_mask)) fail();
	if (!WiFi.softAP(NET_AP_NAME)) fail();

	// Set up DNS server (captive portal)
	dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
	if (!dnsServer.start(53, NET_DNS_NAME, local_ip)) fail();

	// LED to show "done" status
	status_led.setColor(rgbw::black);
	status_led.flush();
	delay(100);
	status_led.setColor(rgbw(COLOR_STATUS_DONE));
	status_led.flush();
}

void loop()
{
	dnsServer.processNextRequest();
	control_server.loop();
	command_reader.update();
	engine.loop();
	output_tilecolors.flush();
}

void fail()
{
	status_led.setColor(rgbw(COLOR_STATUS_ERROR));
	status_led.flush();
	while (true) ;
}