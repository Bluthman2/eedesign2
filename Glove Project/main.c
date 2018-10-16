#include <atmel_start.h>
#include <pwm_basic_example.h>
#include <pwm_basic.h>

//OUTPUT on PB2
volatile PWM_0_register_t PWM_0_duty = 0x3F;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	//==========================================
	// DO NOT DELETE
	atmel_start_init();
	//==========================================
	// Enable pin output
	PWM_0_enable_output_ch1();

	// Set channel 0 duty cycle value register value to specified value
	PWM_0_load_duty_cycle_ch1(PWM_0_duty);

	// Set counter register value
	PWM_0_load_counter(0);

	while (1){}
	return 1;
}
