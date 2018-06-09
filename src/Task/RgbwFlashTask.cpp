#include "RgbwFlashTask.h"
#include "../types.h"
#include "../rgbw.h"
#include <Arduino.h>

RgbwFlashTask::RgbwFlashTask(RgbwLedStripOutput *output, ledId_t led_id, rgbw color, time_t interval, uint8_t repetitions) :
	_output(output),
	_led_id(led_id),
	_color(color),
	_interval(interval),
	_repetitions(repetitions)
{
}

void RgbwFlashTask::setup()
{
	_start_time = millis();
}

bool RgbwFlashTask::loop()
{
	time_t const now = millis();

	// Skip all missed cycles
	while (_repetitions > 0 && now - _start_time >= 2 * _interval)
	{
		_start_time -= 2 * _interval;
		--_repetitions;
	}

	// Check if the task is over
	if (_repetitions == 0)
	{
		_output->setColor(_led_id, _color); // in case we missed a cycle
		return false;
	}

	// At this point, there is at least one repetition left, and the time since the last cycle is < 2 * _interval
	// The value of the output thus depends on whether we are in the interval [0,_interval] or [_interval,2*_interval].
	_output->setColor(_led_id, now - _start_time < _interval ? rgbw::black : _color);
}
