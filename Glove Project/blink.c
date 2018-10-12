#include <atmel_start.h>
#include <avr/io.h>
#include <util/delay.h>
#include <pwm_basic_example.h>


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	//Set PORTC to all outputs
	DDRC = 0xFF;
	//create an infinite loop
	while(1) {
		//this turns pin C0 on and off
		//turns C0 HIGH
		PORTC |=(1<<0);
		//PAUSE 250 miliseconds
		_delay_ms(2000);
		//turns C0 LOW
		PORTC &= ~(1 << 0);
		//PAUSE 250 miliseconds
		_delay_ms(100);
	}
}
