# ThrowReversi

ThrowReversi is a simplified version of the Reversi (Othello) game, but instead of placing disks on a small board, the players need to throw small bags from a certain distance onto a huge board.
The game is best explained by watching [this video](https://www.youtube.com/watch?v=BXUfnJKLoNQ).

## Install

ThrowReversi has been designed for the [Kniwwelino](http://www.kniwwelino.lu/), even though it can be run on every ESP8266-compatible board.

To install ThrowReversi on your Kniwwelino, follow these steps:

1. Prepare your Kniwwelino for use with the Arduino IDE (https://doku.kniwwelino.lu/en/installationarduino)
2. Clone this repository and open it with the Arduino IDE
3. Install the dependencies (see below)
4. Flash it onto your Arduino

Required Arduino libraries (unpack into `./libraries` folder):

* __Keypad__ by Mark Stanley, Alexander Brevig: http://playground.arduino.cc/Code/Keypad
* __Adafruit NeoPixel__ by Adafruit: https://github.com/adafruit/Adafruit_NeoPixel

## License

The software contained in this repository is licensed under an MIT license.
Please read the [LICENSE](LICENSE.md) file for more information.
