#ifndef _KEYBOARDH_
#define _KEYBOARDH_

#include "utils.h"

void keyboard_init(unsigned char *key); 

void keyboard_update(unsigned char key[ALLEGRO_KEY_MAX], ALLEGRO_EVENT *event);

#endif