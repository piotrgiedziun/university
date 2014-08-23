/**
 * arduino duemilanove - atmega328p
 * ================================
 * This code will blink built-in LED (PB5 - pin 13)
 * 16MHz internal oscillator will count
 * from TIMER_START to OVERFLOW
 * This way you can count 1 ms. Then using int counter,
 * you can count up to 1000 ms - 1s.
 * ================================
 * This time we will crate interrupt method,
 * so you dont have to check if overflow occured.
 * ================================
 * Schematic: http://arduino.cc/en/uploads/Main/arduino-duemilanove-schematic.pdf
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#define LED PB5
#define TIMER_START 0XFFFF-16000

// VOLATILE - otherwise it will be removed by compilator
// cuz it's not used in main method
volatile int counter = 0;

int main()
{
	// SET PB5 AS OUTPUT
	DDRB |= _BV(LED);

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
		PORTB |= _BV(LED);
	}else if (counter == 2000) {
		counter = 0;
		PORTB &= ~_BV(LED);
	}
}