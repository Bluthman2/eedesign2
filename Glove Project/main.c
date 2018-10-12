#include <atmel_start.h>
#include <pwm_basic_example.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	PWM_0_test_pwm_basic();
}
