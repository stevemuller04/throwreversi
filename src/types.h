#ifndef INCLUDE_SRC_TYPES_H
#define INCLUDE_SRC_TYPES_H

#include <Arduino.h>

/** The type used to refer to GPIO pins. */
typedef uint8_t pinId_t;

/** The type used to refer to LEDs on an LED strip. */
typedef uint16_t ledId_t;

/** The type used to refer to one coordinate on the game board. */
typedef uint8_t coord_t;

/** The type used to refer to a period of time. Represents a number of milliseconds. */
typedef unsigned long time_t;

#endif
