#ifndef INCLUDE_SRC_INPUT_INPUT_H
#define INCLUDE_SRC_INPUT_INPUT_H

/**
 * Hardware interface that provides functionality to read a value from an attached device.
 */
class Input {
	public:
		/**
		 * Sets the hardware interface up and prepares it for reading.
		 */
		virtual void setup();

		/**
		 * Updates the hardware interface by reading the latest value from the attached device.
		 */
		virtual void update();
};

#endif
