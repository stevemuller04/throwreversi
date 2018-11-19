#ifndef INCLUDE_SRC_TASK_BLINKTASK_H
#define INCLUDE_SRC_TASK_BLINKTASK_H

#include "Task.h"
#include "../Output/BoolPinOutput.h"
#include "../types.h"

#define BLINK_UNDEFINITELY -1

/**
 * Represents a task that repeatedly turns on and off a boolean output.
* After the task, the LED remains off.
 */
class BlinkTask : public Task
{
	private:
		BoolPinOutput * const _output;
		mtime_t const _interval;
		uint8_t _repetitions;
		mtime_t _start_time;
		uint8_t _last_blink_state; // 0 = off, 1 = on, -1 = undetermined

	public:
		/**
		 * Initialises a new blinking task.
		 * @param output - The boolean output to turn on and off.
		 * @param interval - The time interval after which the output is toggled (on > off, or off > on).
		 * @param repetitions - The number of times that the output shall be turned on and off.
		 * For example, repetitions = 2 will turn the output on, off, on, and off.
		 */
		BlinkTask(BoolPinOutput *output, mtime_t interval, uint8_t repetitions);

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
