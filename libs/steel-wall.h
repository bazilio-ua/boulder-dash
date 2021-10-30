#ifndef _STEELWALLH_
#define _STEELWALLH_

#include "utils.h"
#include "sprite.h"

typedef struct STEEL_WALL_STRUCT
{
  int x, y;
} STEEL_WALL_STRUCT;

void steel_wall_init(STEEL_WALL_STRUCT *steelWall, int pos_x, int pos_y);

void steel_wall_draw(STEEL_WALL_STRUCT *steelWall, SPRITES_STRUCT *sprites);

#endif