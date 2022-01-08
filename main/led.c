#include <stdint.h>
#include <task.h>
#include <mcu.h>


/* local/static prototypes */
static void blink(task_t *task);


/* static variables */
static uint8_t period = 0;
static float periods[] = {
	500.0,
	200.0,
};


/* global functions */
void led_init(void){
	pin_write(&led, PIN_CLEAR);
	(void)task_issue(blink, periods[period]);
}


/* local functions */
static void blink(task_t *task){
	period = (period + 1 >= (uint8_t)(sizeof(periods) / sizeof(periods[0]))) ? 0 : period + 1;

	pin_write(&led, PIN_TOGGLE);
	task_update_period(task, periods[period]);
}
