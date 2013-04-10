/**
 * arduino duemilanove - atmega328p
 * ================================
 * This code will count from 10 to 0.
 * HAPPY NEW YEAR!!
 * Used pins 8-13 (PB0-PB5)
 * ================================
 * Schematic: http://arduino.cc/en/uploads/Main/arduino-duemilanove-schematic.pdf
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED PB5
#define TIMER_START 0XFFFF-16000

volatile int counter = 0;
volatile int new_year_counter = 10;
int main()
{
    // SET ALL PORT B AS OUTPUT
	DDRB = 0xFFFFF;

	// SET TIMER COUNT
	TCNT1  = TIMER_START;
	// ENABLE OVERFLOW INTERRUPT
	TIMSK1 = (1 << TOIE1);
	
	// ENABLE INTERRUPTS
	sei();

	// CONFIGURE TIMER
	TCCR1A = 0x00;		// NORMAL
	TCCR1B = _BV(CS10); // clkI/O/1 (No prescaling)
	TCCR1C = 0x00;		// COUNTER
	
	while(1);

	return 0;
}

ISR(TIMER1_OVF_vect) {  
	// SET TIMER COUNT
	TCNT1  = TIMER_START;

	counter++;
	if (counter == 1000) {
		counter = 0;
		PORTB = ~new_year_counter;

		new_year_counter--;
		if (new_year_counter == -1) {
			new_year_counter = 10;
		}
	}
}