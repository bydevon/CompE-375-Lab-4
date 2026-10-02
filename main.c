/*
 * Lab 4.c
 *
 * Created: 10/1/2026 7:09:27 PM
 * Author : Devon
 */ 

#define F_CPU 16000000UL // telling the debugger that it is running at 16MHz
#include <avr/io.h>



// pseudo code implementation

/*
 we need PWM period to be 10ms 
 we use prescaler = 1024, math is f(timer) = 16Mhz/2024 = 15625Hz
 T(tick) = 1/15625 = 64 micro seconds
 we need about 10ms / 64 micro seconds = 156.25 counts
*/

// brightness ramp = 0% - 100% in about 1s

// Pushbutton SW200 is located at PB7, page 12 of the user guide
// Yellow LED D200 is located at PB5, page  of the user guide


int main(void)
{
	TCCR0A |= (1 << WGM01); // Setting the timer mode to CTC
	OCR0A = 155; //0xF9
	OCR0B = 0x10;
	
	TCCR0B |= (1 << CS02) | (1 << CS00); // setting the pre-scaler to 256 and starting the timer
	while (1)
	{
		while ( (TIFR0 & (1 << OCF0B)) == 0) {} // waiting the OCR0B overflow event
		
		
		/* if (buttonPressed) {
			
		increase brightness to 100%
		
		
		} 
		else {
			decrease brightness to 0%
		}
		
		update PWM duty cycle
		*/
		
		
		
	}
}
