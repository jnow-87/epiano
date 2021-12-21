#include <avr/io.h>


/* global functions */
void mcu_init(void){
	// disable peripherals
	PRR = 0xff;
}
