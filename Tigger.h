// We use 4-character tabstops, so IN VIM:  <esc>:set ts=4
// // ...that's: ESCAPE key, colon key, then "s-e-t SPACE key t-s-=-4"
/*
 * Tigger.h - A library for reading a switch from an Arduino digital pin.
 * Why Tigger?  "Because I'm a Tigger, and Tiggers bounce!"
 *
 * Copyright 2011 Michael Schwager (aka, "GreyGnome")
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Questions?  Send mail to mschwage@gmail.com
 *  ---- VERSIONS ----------------------------------------------------------------------------
 *  0.1 Wed Jan 18 07:36:33 CST 2012
 *  Initial revision.  This should be the last one, because there are no bugs and it is
 *  completely featureful.  Heh.
 *  ---- VERSIONS ----------------------------------------------------------------------------
*/

#ifndef Tigger_h
#define Tigger_h

#include "stdint.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include "pins_arduino.h"
  #include "WProgram.h"
  #include "wiring.h"
#endif

#define LIBCALL_OOPINCHANGEINT
#include "../ooPinChangeInt/ooPinChangeInt.h"

#include "../cbiface/cbiface.h"

#undef DEBUG

#define DEFAULTDELAY 10
/*
 * Triggers for the tigger:
	CHANGE to trigger the interrupt whenever the pin changes value
	RISING to trigger when the pin goes from low to high,
	FALLING for when the pin goes from high to low.
*/
class Tigger : public CallBackInterface {
	public:
		Tigger(uint8_t arduinoPin) : count(0), _arduinoPin(arduinoPin), _trigger(CHANGE), _resistor(HIGH), _delay(DEFAULTDELAY), _startTime(0) {
			init();
		}
		Tigger(uint8_t arduinoPin, uint8_t TiggerTrigger) :
			count(0), _arduinoPin(arduinoPin), _trigger(TiggerTrigger), _resistor(HIGH), _delay(DEFAULTDELAY), _startTime(0) {
			init();
		}
		Tigger(uint8_t arduinoPin, uint8_t TiggerTrigger, uint8_t resistor) :
			count(0), _arduinoPin(arduinoPin), _trigger(TiggerTrigger), _resistor(resistor), _delay(DEFAULTDELAY), _startTime(0) {
			init();
		}
		Tigger(uint8_t arduinoPin, uint8_t TiggerTrigger, uint8_t resistor, uint8_t Delay) :
			count(0), _arduinoPin(arduinoPin), _trigger(TiggerTrigger), _resistor(resistor), _delay(Delay), _startTime(0) {
			init();
		}
		uint16_t getCount(); // read the number of state changes from the switch.  Reset the count to 0 upon read.
		uint16_t getCountNoReset(); // Do the same, but no reset.
		uint8_t getPin(); // return the arduino pin for this Tigger
		void cbmethod();  // required method for a subclass of CallBackInterface
		unsigned long getStartTime();
		unsigned long getMillis();
		static uint8_t wonderful(); // "The wonderful thing about tiggers..."
	protected:
		uint8_t _arduinoPin;
		uint8_t _delay;
		uint16_t count;
		uint8_t _resistor;
		uint8_t _trigger;
		long _startTime;
	private:
		void init();
};
#endif
