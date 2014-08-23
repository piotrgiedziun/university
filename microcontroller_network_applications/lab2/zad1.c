/**
 * arduino duemilanove - atmega328p
 * ================================
 * This code will blink built-in LED (PB5 - pin 13)
 * with 1 sec delay
 * ================================
 * Schematic: http://arduino.cc/en/uploads/Main/arduino-duemilanove-schematic.pdf
 */
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LED PB5

int main()
{
	// SET PB5 AS OUTPUT
	DDRB |= _BV(LED);

	while(1) {
		// BLINK LED
		PORTB |= _BV(LED);
		_delay_ms(1000);
		PORTB &= ~_BV(LED);
		_delay_ms(1000);
	}

	return 0;
}