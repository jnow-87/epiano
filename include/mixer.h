#ifndef MIXER_H
#define MIXER_H


#include <stdint.h>


/* prototypes */
void mixer_init(void);

void mixer_play(char note);
void mixer_revoke(char note);

void mixer_div(int8_t inc);


#endif // MIXER_H
