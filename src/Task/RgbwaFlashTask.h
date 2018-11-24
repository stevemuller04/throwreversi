#ifndef INCLUDE_SRC_TASK_RGBWAFLASHTASK_H
#define INCLUDE_SRC_TASK_RGBWAFLASHTASK_H

#include "Task.h"
#include "../Control/LedMatrixOutputManager.h"
#include "../types.h"

#define FLASH_UNDEFINITELY -1

/**
 * Represents a task that lets an RGBW LED flash a certain number of times.
 * After the task, the LED remains on.
 */
class RgbwaFlashTask : public Task
{
	private:
		LedMatrixOutputManager * const _output;
		coord_t const _x;
		coord_t const _y;
		rgbwa const _initial_color;
		rgbwa const _final_color;
		mtime_t const _interval;
		uint8_t _repetitions;
		mtime_t _start_time;
		uint8_t _last_blink_state; // 0 = off, 1 = on, -1 = undetermined

	public:
		/**
		 * Initialises a new flashing task.
		 * @param output - The RGBW LED output to flash.
		 * @param x - The x coordinate of the RGBW LED in the LED matrix.
		 * @param y - The y coordinate of the RGBW LED in the LED matrix.
		 * @param color - The RGBWA overlay color for the LED in the matrix.
		 * @param interval - The time interval after which the output is toggled (on > off, or off > on).
		 * @param repetitions - The number of times that the output shall flash (= turned off and on).
		 * For example, repetitions = 2 will turn the output off, on, off, on.
		 */
		RgbwaFlashTask(LedMatrixOutputManager *output, coord_t x, coord_t y, rgbwa initial_color, rgbwa final_color, mtime_t interval, uint8_t repetitions);

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
