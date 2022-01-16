#include <config/config.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include <task.h>


/* macros */
#define TIMER_HZ	(CONFIG_MCU_CLOCK_HZ / 8)
#define TICKS_HZ	10000


/* local/static prototypes */
static size_t ticks(float period_ms);


/* global variables */
static task_t *tasks = 0x0;


/* global functions */
void task_init(void){
	PRR &= ~(0x1 << PRTIM0);

	TCCR0A = (0x2 << WGM00);
	TCCR0B = (0x2 << CS10);
	TIMSK0 = (0x1 << OCIE0A);

	OCR0A = TIMER_HZ / TICKS_HZ;
	TCNT0 = 0;
}

task_t *task_issue(task_hdlr_t hdlr, float period_ms){
	task_t *task;


	task = malloc(sizeof(task_t));

	if(task == 0x0){
		printf("out of memory\n");
		return 0x0;
	}

	task->hdlr = hdlr;
	task->period_ms = period_ms;
	task->ticks = ticks(period_ms);

	list_add_tail(&tasks, task);

	printf("new task %p\n", task);

	return task;
}

void task_terminate(task_t *task){
	list_rm(&tasks, task);
	free(task);
}

void task_update_period(task_t *task, float period_ms){
	task->period_ms = period_ms;
}


/* interrupt handlers */
SIGNAL(TIMER0_COMPA_vect){
	task_t *task;


	list_for_each(tasks, task){
		task->ticks--;

		if(task->ticks != 0)
			continue;

		task->hdlr(task);
		task->ticks = ticks(task->period_ms);
		task_update_period(task, task->period_ms);
	}
}


/* local functions */
static size_t ticks(float period_ms){
	size_t ticks = (TICKS_HZ / 1000) * period_ms;

	if(ticks == 0)
		return 1;

	return ticks;
}
