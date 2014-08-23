/**
 * arduino duemilanove - atmega328p
 * ================================
 * This code will blink built-in LED (PB5 - pin 13)
 * 16MHz internal oscillator will count
 * from TIMER_START to OVERFLOW
 * This way you can count 1 ms. Then using int counter,
 * you can count up to 1000 ms - 1s.
 * ================================
 * Schematic: http://arduino.cc/en/uploads/Main/arduino-duemilanove-schematic.pdf
 */

#include <avr/io.h>

#define LED PB5
#define TIMER_START 0XFFFF-16000

int main()
{
	int counter = 0;
	// SET PB5 AS OUTPUT
	DDRB |= _BV(LED);

	// SET TIMER COUNT
	TCNT1  = TIMER_START;

	// CONFIGURE TIMER
	TCCR1A = 0x00;		// NORMAL
	TCCR1B = _BV(CS10); // clkI/O/1 (No prescaling)
	TCCR1C = 0x00;		// COUNTER
	
	while (1) {
		// TOV1 - Timer/Counter1, Overflow Flag
		// TIFR1 - Timer/Counter1 Interrupt Flag Register
		// IF OVERFLOW INTERRUPT OCCURED
		if (TIFR1 & _BV(TOV1)) {
			// CLEAR OVERFLOW FLAG
			TIFR1 = _BV(TOV1);
			// SET TIMER COUNT
			TCNT1  = TIMER_START;

			// BLINK LED
			counter++;
			if (counter == 1000) {
				PORTB |= _BV(LED);
			}else if (counter == 2000) {
				counter = 0;
				PORTB &= ~_BV(LED);
			}
		}
	}

	return 0;
}