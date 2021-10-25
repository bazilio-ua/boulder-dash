#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#define BUFFER_WIDTH 320
#define BUFFER_HEIGHT 240
#define DISPLAY_SCALE 3
#define DISPLAY_WIDTH (BUFFER_WIDTH * DISPLAY_SCALE)
#define DISPLAY_HEIGHT (BUFFER_HEIGHT * DISPLAY_SCALE)
#define KEY_SEEN 1
#define KEY_RELEASED 2

void initialize(bool isInitialized, const char *description); 
