#include <config/config.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <task.h>
#include <mixer.h>


/* local/static prototypes */
static void play_melody(task_t *task);


/* static variables */
static char secret[] = CONFIG_SECRET;
static uint8_t sindex = 0;


/* global functions */
bool secret_solved(char c){
	printf("secret check: %c vs. %s[%u] = %c\n", c, secret, sindex, secret[sindex]);

	if(secret[sindex++] != c){
		sindex = (secret[0] == c) ? 1 : 0;

		return false;
	}

	if(secret[sindex] == 0){
		printf("secret solved\n");

		task_issue(play_melody, CONFIG_SECRET_MELODY_INTERVAL_MS);
		sindex = 0;

		return true;
	}

	return false;
}


/* local functions */
static void play_melody(task_t *task){
	static uint8_t i = 0;
	static uint8_t play = 1;
	static char melody[] = CONFIG_SECRET_MELODY;


	if(play)	mixer_play(melody[i]);
	else		mixer_revoke(melody[i++]);

	play ^= 1;

	if(melody[i] == 0){
		i = 0;
		task_terminate(task);
	}
}
