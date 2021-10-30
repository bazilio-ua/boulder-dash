#ifndef _BOULDERH_
#define _BOULDERH_

#include "utils.h"
#include "sprite.h"

typedef struct BOULDER_STRUCT
{
  int x, y;
} BOULDER_STRUCT;

void boulder_init(BOULDER_STRUCT *boulder, int pos_x, int pos_y); 

void boulder_update(BOULDER_STRUCT *boulder, SPRITES_STRUCT *sprites, long int count);

void boulder_draw(BOULDER_STRUCT *boulder, SPRITES_STRUCT *sprites); 

#endif