#ifndef _ROCKFORDH_
#define _ROCKFORDH_

#include "utils.h"
#include "sprite.h"
#include "explosion.h"

typedef struct ROCKFORD_STRUCT
{
  int x, y;
  int lives;
  int respawn_timer;
  int invincible_timer;
  int direction;
  int last_direction;
  int source_x;
  int source_y;
  int score;
  int quantity_of_diamonds;
  bool active;
  bool redraw;
} ROCKFORD_STRUCT;

ROCKFORD_STRUCT *allocate_rockford();

void rockford_init(ROCKFORD_STRUCT *rockford, int pos_x, int pos_y);

void rockford_update(
    ROCKFORD_STRUCT *rockford,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    ALLEGRO_KEYBOARD_STATE *keyState,
    SPRITES_STRUCT *sprites,
    long int count);

void rockford_draw(ROCKFORD_STRUCT *rockford, SPRITES_STRUCT *sprites);

void rockford_free(ROCKFORD_STRUCT *rockford);

#endif