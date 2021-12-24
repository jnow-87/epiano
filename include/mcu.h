#ifndef MCU_H
#define MCU_H


#include <port.h>


/* external variables */
extern port_t *ports[];
extern port_t pb,
			  pc,
			  pd;

extern pin_t speaker,
			 led,
			 motor,
			 keys[],
			 pedals[];


/* prototypes */
void mcu_init(void);


#endif // MCU_H
