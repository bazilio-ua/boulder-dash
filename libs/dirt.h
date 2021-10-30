#ifndef _DIRTH_
#define _DIRTH_

#include "utils.h"
#include "sprite.h"

typedef struct DIRT_STRUCT
{
  int x, y;
} DIRT_STRUCT;

void dirt_init(DIRT_STRUCT *dirt, int pos_x, int pos_y); 

void dirt_update(DIRT_STRUCT *dirt, SPRITES_STRUCT *sprites, long int count);

void dirt_draw(DIRT_STRUCT *dirt, SPRITES_STRUCT *sprites); 

#endif