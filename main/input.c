#include <avr/interrupt.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mcu.h>
#include <uart.h>
#include <port.h>
#include <mixer.h>
#include <motor.h>
#include <secret.h>


/* local/static prototypes */
static void key_pressed(char key);
static void key_released(char key);

static bool isnote(char key);

static void decode_port_key(port_t *port);


/* local functions */
static void key_pressed(char key){
	printf("%c pressed\n", key);

	if(!isnote(key))
		return;

	mixer_play(key);

	if(secret_solved(key))
		motor_activate();
}

static void key_released(char key){
	printf("%c released\n", key);

	switch(key){
	case '+':
		mixer_div(10);
		break;

	case '-':
		mixer_div(-10);
		break;

	case 'm':
		motor_activate();
		break;

	default:
		if(isnote(key))
			mixer_revoke(key);
		break;
	}
}

static bool isnote(char key){
	char skey[] = { key, 0x0 };


	if(strstr("cdefgahn", skey) == 0x0)
		return false;
	return true;
}

static void decode_port_key(port_t *port){
	uint8_t new = port_read(port),
			old = port->pin_val,
			diff = old ^ new;
	uint8_t i;


	for(i=0; i<8; i++){
		if(!(diff & (0x1 << i)))
			continue;

		if((old & (0x1 << i)))	key_pressed(port->pins[i]->key);
		else					key_released(port->pins[i]->key);
	}

	port->pin_val = new;
}


/* interrupt handlers */
SIGNAL(USART_RX_vect){
	char key = uart_getc();

	if(!isalpha(key))		key_released(key);
	else if(isupper(key))	key_released(tolower(key));
	else					key_pressed(key);
}

SIGNAL(PCINT0_vect){
	decode_port_key(&pb);
}

SIGNAL(PCINT1_vect){
	decode_port_key(&pc);
}

SIGNAL(PCINT2_vect){
	decode_port_key(&pd);
}
