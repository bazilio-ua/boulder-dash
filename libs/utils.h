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

#define ROCKFORD_WIDTH 32
#define ROCKFORD_HEIGHT 32
#define ROCKFORD_SPEED 3
#define ROCKFORD_MAX_X (BUFFER_WIDTH - ROCKFORD_WIDTH)
#define ROCKFORD_MAX_Y (BUFFER_HEIGHT - ROCKFORD_HEIGHT)
#define NO_DIRECTION -1
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

#define DIAMOND_WIDTH 32
#define DIAMOND_HEIGHT 32

#define FIREFLY_WIDTH 32
#define FIREFLY_HEIGHT 32

#define AMOEBA_WIDTH 32
#define AMOEBA_HEIGHT 32

void initialize(bool isInitialized, const char *description); 
