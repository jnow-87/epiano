#include <stdint.h>
#include <stdio.h>
#include <port.h>
#include <mcu.h>
#include <task.h>


/* local/static prototypes */
static void speak(task_t *task);
static float note_delay_ms(char note);


/* static variables */
static uint8_t div = 1;
static uint8_t play = 0;
static task_t *task = 0x0;


/* global functions */
void mixer_init(void){
	task = task_issue(speak, 10);
}

void mixer_play(char note){
	printf("play note: %c\n", note);

	play = 1;
	task_update_period(task, note_delay_ms(note) / div);
}

void mixer_revoke(char note){
	printf("revoke note: %c\n", note);

	play = 0;
	task_update_period(task, 10);
}

void mixer_div(int8_t inc){
	if(inc > 0 && (uint8_t)(div + inc) < div)	return;
	if(inc < 0 && (uint8_t)(div + inc) > div)	return;

	div += inc;
	printf("set mixer divider: %hhu\n", div);
}


/* local functions */
static void speak(task_t *t){
	if(!play)	pin_write(&speaker, PIN_CLEAR);
	else		pin_write(&speaker, PIN_TOGGLE);
}

static float note_delay_ms(char note){
	switch(note){
	case 'c':	return 6.0;
	case 'd':	return 5.4;
	case 'e':	return 4.8;
	case 'f':	return 4.5;
	case 'g':	return 4.0;
	case 'a':	return 3.6;
	case 'h':	return 3.2;
	case 'n':	return 10.0;
	default:	return 10.0;
	}
}
