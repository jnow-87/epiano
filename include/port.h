#ifndef PORT_H
#define PORT_H


#include <stdint.h>


/* incomplete types */
struct pin_t;


/* types */
typedef enum{
	PIN_IN = 0,
	PIN_OUT,
} pin_dir_t;

typedef enum{
	PIN_SET = 0,
	PIN_CLEAR,
	PIN_TOGGLE
} pin_state_t;

typedef struct{
	// port registers
	uint8_t volatile *ddr,
					 *port,
					 *pin,
					 *pcmsk;

	// pin change interrupt number
	uint8_t pcint;

	// pin configuration
	struct pin_t *pins[8];

	// runtime data
	uint8_t pin_val,	// last PINx register value
			pin_mask;	// bit mask for configured pins
} port_t;

typedef struct pin_t{
	// port allocation
	port_t *port;
	uint8_t bit;

	pin_dir_t dir;

	char key;	// keyboard char associated with the pin
				// only relevant for input pins
} pin_t;


/* prototypes */
void ports_init(void);

uint8_t port_read(port_t *port);

pin_state_t pin_read(pin_t *pin);
void pin_write(pin_t *pin, pin_state_t state);


#endif // PORT_H
