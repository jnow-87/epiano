#include <avr/io.h>
#include <port.h>
#include <mcu.h>


/* global variables */
port_t *ports[] = {
	&pb,
	&pc,
	&pd,
	0x0
};

// ports
port_t pb = {
	.ddr = &DDRB,
	.port = &PORTB,
	.pin = &PINB,
	.pcmsk = &PCMSK0,
	.pcint = 0,
	.pins = {
		&motor,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		pedals + 0,
		pedals + 1,
	},
};

port_t pc = {
	.ddr = &DDRC,
	.port = &PORTC,
	.pin = &PINC,
	.pcmsk = &PCMSK1,
	.pcint = 1,
	.pins = {
		keys + 0,
		keys + 1,
		keys + 2,
		keys + 3,
		keys + 4,
		keys + 5,
		0x0,
		0x0,
	},
};

port_t pd = {
	.ddr = &DDRD,
	.port = &PORTD,
	.pin = &PIND,
	.pcmsk = &PCMSK2,
	.pcint = 2,
	.pins = {
		0x0,
		0x0,
		&led,
		&speaker,
		0x0,
		keys + 6,
		keys + 7,
		0x0,
	},
};

// pins
pin_t speaker = { .port = &pd, .bit = 3, .dir = PIN_OUT, .key = 0 };
pin_t led = { .port = &pd, .bit = 2, .dir = PIN_OUT, .key = 0 };
pin_t motor = { .port = &pb, .bit = 0, .dir = PIN_OUT, .key = 0 };
pin_t keys[] = {
	{ .port = &pc, .bit = 0, .dir = PIN_IN, .key = 'c' },
	{ .port = &pc, .bit = 1, .dir = PIN_IN, .key = 'd' },
	{ .port = &pc, .bit = 2, .dir = PIN_IN, .key = 'e' },
	{ .port = &pc, .bit = 3, .dir = PIN_IN, .key = 'f' },
	{ .port = &pc, .bit = 4, .dir = PIN_IN, .key = 'g' },
	{ .port = &pc, .bit = 5, .dir = PIN_IN, .key = 'a' },
	{ .port = &pd, .bit = 5, .dir = PIN_IN, .key = 'h' },
	{ .port = &pd, .bit = 6, .dir = PIN_IN, .key = 'n' },
};
pin_t pedals[] = {
	{ .port = &pb, .bit = 6, .dir = PIN_IN, .key = '+' },
	{ .port = &pb, .bit = 7, .dir = PIN_IN, .key = '-' },
};


/* global functions */
void mcu_init(void){
	// disable peripherals
	PRR = 0xff;
}
