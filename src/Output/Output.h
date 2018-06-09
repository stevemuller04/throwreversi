#ifndef INCLUDE_SRC_OUTPUT_OUTPUT_H
#define INCLUDE_SRC_OUTPUT_OUTPUT_H

/**
 * Hardware interface that provides functionality to control an attached device.
 */
class Output {
	public:
		/**
		 * Sets the hardware interface up and prepares it for being controlled.
		 */
		virtual void setup() = 0;

		/**
		 * Sends all commands which have been buffered in this hardware interface to the attached device.
		 */
		virtual void flush() = 0;
};

#endif
