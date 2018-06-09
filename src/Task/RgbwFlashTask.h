#ifndef INCLUDE_SRC_TASK_RGBWFLASHTASK_H
#define INCLUDE_SRC_TASK_RGBWFLASHTASK_H

#include "Task.h"
#include "../Output/RgbwLedStripOutput.h"
#include "../types.h"

/**
 * Represents a task that lets an RGBW LED flash a certain number of times.
 * After the task, the LED remains on.
 */
class RgbwFlashTask : public Task
{
	private:
		RgbwLedStripOutput * const _output;
		ledId_t const _led_id;
		rgbw const _color;
		mtime_t const _interval;
		uint8_t _repetitions;
		mtime_t _start_time;

	public:
		/**
		 * Initialises a new flashing task.
		 * @param output - The RGBW LED output to flash.
		 * @param led_id - The index of the RGBW LED in the LED strip.
		 * @param color - The RGBW color in which the LED shall flash.
		 * @param interval - The time interval after which the output is toggled (on > off, or off > on).
		 * @param repetitions - The number of times that the output shall flash (= turned off and on).
		 * For example, repetitions = 2 will turn the output off, on, off, on.
		 */
		RgbwFlashTask(RgbwLedStripOutput *output, ledId_t led_id, rgbw color, mtime_t interval, uint8_t repetitions);

		/**
		 * @see Task::setup()
		 */
		virtual void setup() override;

		/**
		 * @see Task::loop()
		 */
		virtual bool loop() override;
};

#endif
