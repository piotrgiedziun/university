/**
 * arduino duemilanove - atmega328p
 * ================================
 * This code will blink built-in LED (PB5 - pin 13) and external LED (PB4 - pin 12)
 * Timer1 is 16 bytes so you can count 16000 times (cuz max is 65535 > 16000)
 * but Timer2 is 8 bytes so you cant count up to 16000 times (255 is maximum value),
 * so in order to use it as 1 ms interrupt you have to slow it 256 times.
 * This way you will be counting from 0xFF-62.
 * ================================
 * Schematic: http://arduino.cc/en/uploads/Main/arduino-duemilanove-schematic.pdf
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED PB5
#define LED2 PB4
// TIMER1 - 16 bits -> 65535 max
#define TIMER_START 0xFFFF-16000
// TIMER2 - 8 bit -> 255 max
#define TIMER2_START 0xFF-62

volatile int counter = 0;
volatile int counter2 = 0;
int main()
{
	DDRB = 0xFFFF;

	// SET TIMER COUNT
	TCNT1 = TIMER_START;
	TCNT2 = TIMER2_START;

	// ENABLE OVERFLOW INTERRUPT
	TIMSK1 = (1 << TOIE1);
	TIMSK2 = (1 << TOIE2);

	// ENABLE INTERRUPT
	sei();

	// CONFIGURE TIMER 1
	TCCR1A = 0x00;		// NORMAL
	TCCR1B = _BV(CS10); // clkI/O/1 (No prescaling)
	TCCR1C = 0x00;		 // COUNTER
	
	// CONFIGURE TIMER 2
	TCCR2A = 0x00;		// NORMAL
	TCCR2B = _BV(CS22) | _BV(CS21); // 256 TIMES SLOWER

	while(1);

	return 0;
}

ISR(TIMER2_OVF_vect) {  
	// SET TIMER2 COUNT
	TCNT2  = TIMER2_START;

	counter2++;
	if (counter2 == 1000) {
		PORTB |= _BV(LED2);
	}else if (counter == 2000) {
		counter2 = 0;
		PORTB &= ~_BV(LED2);
	}
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