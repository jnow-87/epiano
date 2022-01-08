#include <config/config.h>
#include <util/delay.h>
#include <stdio.h>
#include <mcu.h>
#include <port.h>


/* global functions */
void motor_init(void){
	pin_write(&motor, PIN_SET);
}

void motor_activate(void){
	printf("activate motor\n");

	pin_write(&motor, PIN_CLEAR);
	_delay_ms(CONFIG_MOTOR_IMPULSE_MS);
	pin_write(&motor, PIN_SET);
}
