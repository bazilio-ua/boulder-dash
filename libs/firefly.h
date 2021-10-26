#ifndef _FIREFLYH_
#define _FIREFLYH_

#include "utils.h"
#include "sprite.h"

typedef struct FIREFLY_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
} FIREFLY_STRUCT;

void firefly_init(FIREFLY_STRUCT *firefly, int pos_x, int pos_y); 

void firefly_update(FIREFLY_STRUCT *firefly, SPRITES_STRUCT *sprites);

void firefly_draw(FIREFLY_STRUCT *firefly, SPRITES_STRUCT *sprites); 

#endif