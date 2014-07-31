// We use 4-character tabstops, so IN VIM:  <esc>:set ts=4 sw=4 sts=4
// ...that's: ESCAPE key, colon key, then "s-e-t SPACE key t-s-=-4"
/*
 * Tigger.cpp - A library for reading a switch from an Arduino digital pin.
 * Why Tigger?  "Because I'm a Tigger, and Tiggers bounce!"
 *
Copyright 2011,2012,2013,2014 Michael Anthony Schwager

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

        Questions?  Send mail to mschwage@gmail.com
*/

#include "Tigger.h"

# define cli()  __asm__ __volatile__ ("cli" ::)
# define sei()  __asm__ __volatile__ ("sei" ::)

//#undef DEBUG

/*
 * NOTES
 * This library handles switches attached to an Arduino digital input pin.  Analog
 * pins are handled, of course, because the analog pins can be used as digital inputs
 * as well.
 *
 * The library is interrupt-driven and designed to be fast and easy to use.  The interrupt
 * routine is lightweight, and the programmer is then able to read the state of the switch
 * or the number of presses at their leisure.
*/

/*
 */


// DEBUG: volatile uint8_t *port;
void Tigger::init() {
	volatile uint8_t *port=portInputRegister(digitalPinToPort(_arduinoPin));
	if (port == NOT_A_PIN) { return; }
	pinMode(_arduinoPin, INPUT);
	digitalWrite(_arduinoPin, _resistor);
	// DEBUG: port=portInputRegister(digitalPinToPort(_arduinoPin));

	PCintPort::attachInterrupt(_arduinoPin, this, _trigger);
};

extern volatile unsigned long timer0_millis; // From the Arduino wiring.h file.
unsigned long tigermillis=0;

/*
 * Interrupt has been triggered.
 */
void Tigger::cbmethod() {
	if (_delay != 0) {
		uint8_t oldSREG = SREG;

		// the next 3 code lines are from the wiring.c arduino code
		// disable interrupts while we read timer0_millis or we might get an
		// inconsistent value (e.g. in the middle of a write to timer0_millis)
		cli();
		// DEBUG: volatile uint8_t lastPinView=*portInputRegister(4);
		tigermillis = timer0_millis;
		SREG = oldSREG;

		/*
	 	* Algorithm:
	 	* if millis - _startTime <= delay, bounce.  Do nothing.
	 	* if millis - _startTime > delay, new press: increment count.
	 	*/
		if (tigermillis-_startTime <= _delay) return;

		_startTime=tigermillis;
	}
	count++;
}


/*
 * Returns the count of the button presses.  Upon reading, resets to 0.
 */
uint16_t Tigger::getCount() {
	uint16_t val;
	val=count; count=0;
	return val;
}

/*
 * Returns the count of the button presses.
 */
uint16_t Tigger::getCountNoReset() {
	return count;
}

/*
 * Returns the Arduino Pin for this Tigger
 */
uint8_t Tigger::getPin() {
	return _arduinoPin;
}

/*
 * startTime is the millis() value when the last switch transition was recorded. 
 * millis() is the Arduino call that returns the number of milliseconds since the Arduino was reset.
 * It is a 32-bit unsigned number.
 */
unsigned long Tigger::getStartTime() {
	return _startTime;
}

/*
 * Returns the millis() value when the latest switch transition caused an interrupt, which includes bounces.
 */
unsigned long Tigger::getMillis() {
	return tigermillis;
}

/*
 * The wonderful thing about Tiggers, is I'm the only one!
 */
uint8_t Tigger::wonderful() {
	return 1;
}
