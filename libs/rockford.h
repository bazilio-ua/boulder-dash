#ifndef _ROCKFORDH_
#define _ROCKFORDH_

#include "utils.h"
#include "sprite.h"

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
} ROCKFORD_STRUCT;

void rockford_init(ROCKFORD_STRUCT *rockford);

void rockford_update(
    ROCKFORD_STRUCT *rockford, 
    ALLEGRO_KEYBOARD_STATE *keyState, 
    SPRITES_STRUCT *sprites,
    long int count
    );

void rockford_draw(ROCKFORD_STRUCT *rockford, SPRITES_STRUCT *sprites);

#endif