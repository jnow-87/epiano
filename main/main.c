#include <avr/interrupt.h>
#include <stdio.h>
#include <mcu.h>
#include <uart.h>
#include <port.h>
#include <task.h>
#include <led.h>
#include <mixer.h>
#include <motor.h>


/* global functions */
int main(){
	mcu_init();
	uart_init();
	ports_init();
	task_init();
	led_init();
	mixer_init();
	motor_init();

	sei();

	printf("reset ePiano\n");

	while(1){
		asm volatile("sleep");
	}
}
