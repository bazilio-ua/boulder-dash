#ifndef _BUTTERFLYH_
#define _BUTTERFLYH_

#include "utils.h"
#include "sprite.h"

typedef struct BUTTERFLY_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
} BUTTERFLY_STRUCT;

void butterfly_init(BUTTERFLY_STRUCT *butterfly, int pos_x, int pos_y); 

void butterfly_update(BUTTERFLY_STRUCT *butterfly, SPRITES_STRUCT *sprites, long int count);

void butterfly_draw(BUTTERFLY_STRUCT *butterfly, SPRITES_STRUCT *sprites); 

#endif