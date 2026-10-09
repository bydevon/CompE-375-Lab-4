/*
 * Lab 4.c
 *
 * Created: 10/1/2026 7:09:27 PM
 * Author : Devon Ellison
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

#define LEDOn (PORTB |= (1 << PORTB5))
#define LEDOff (PORTB &= ~(1 << PORTB5))
#define clearFlagA (TIFR0 = (1 << OCF0A))

// Pushbutton SW200 is located at PB7, page 12 of the user guide
// Yellow LED D200 is located at PB5

int main(void)
{
	unsigned char dutyCycle = 0; // unsigned for no negative numbers
	unsigned char pwmCount = 0;
	
	// Configure LED and Button
	DDRB |= (1 << DDB5);    // PB5 output (LED)
	DDRB &= ~(1 << DDB7);   // PB7 input (button)
	PORTB |= (1 << PORTB7); // Enable pull-up resistor
	
	LEDOff;
	
	TCCR0A |= (1 << WGM01); // Setting the timer mode to CTC
	OCR0A = 199; // 100 microseconds per compare match
	
	TCNT0 = 0; // reset timer counter
	clearFlagA;
	TCCR0B = (1 << CS01); // Starting the timer, prescaler set at 8
	
	while (1)
	{
		// Wait for 100 microseconds
		while ((TIFR0 & (1 << OCF0A)) == 0){}
		clearFlagA;

		// Control LED brightness
		if (pwmCount < dutyCycle)
		{
			LEDOn;
		}
		else
		{
			LEDOff;
		}

		pwmCount++;

		// 100 counts = 10 milliseconds
		if (pwmCount == 100)
		{
			pwmCount = 0;

			// Button pressed
			if (!(PINB & (1 << PINB7)))
			{
				if (dutyCycle < 100)
				{
					dutyCycle++;
				}
			}
			else // Button released
			{
				if (dutyCycle > 0)
				{
					dutyCycle--;
				}
			}
		}
	}
}
