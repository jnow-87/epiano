#include <avr/io.h>
#include <port.h>
#include <mcu.h>


/* local/static prototypes */
static void pin_init(pin_t *pin, pin_dir_t dir);


/* global functions */
void ports_init(void){
	uint8_t i,
			j;
	pin_t *pin;


	// enable port pull-ups
	MCUCR &= ~(0x1 << PUD);

	// configure pins
	for(i=0; ports[i]!=0x0; i++){
		for(j=0; j<8; j++){
			pin = ports[i]->pins[j];

			if(pin == 0x0)
				continue;

			pin_init(pin, pin->dir);
		}
	}
}

uint8_t port_read(port_t *port){
	return *port->pin & port->pin_mask;
}

pin_state_t pin_read(pin_t *pin){
	return (*pin->port->pin >> pin->bit) & 0x1;
}

void pin_write(pin_t *pin, pin_state_t state){
	uint8_t v = (0x1 << pin->bit);
	uint8_t volatile *port = pin->port->port;


	if(state == PIN_SET)		*port &= ~v;
	else if(state == PIN_CLEAR)	*port |= v;
	else						*port ^= v;
}


/* local functions */
static void pin_init(pin_t *pin, pin_dir_t dir){
	uint8_t bit = pin->bit;
	port_t *port = pin->port;


	*port->ddr |= (dir << bit);
	*port->ddr &= ~((dir ^ 0x1) <<  bit);

	*port->pcmsk |= ((dir ^ 0x1) << bit);
	*port->pcmsk &= ~(dir <<  bit);

	*port->port |= (0x1 << bit);

	if(dir == PIN_IN)
		port->pin_mask |= (0x1 << bit);

	port->pin_val = port_read(pin->port);

	PCICR |= (0x1 << port->pcint);
}
