#ifndef _MAGICWALLH_
#define _MAGICWALLH_

#include "utils.h"
#include "sprite.h"

typedef struct MAGIC_WALL_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
} MAGIC_WALL_STRUCT;

void magic_wall_init(MAGIC_WALL_STRUCT *magicWall, int pos_x, int pos_y); 

void magic_wall_update(MAGIC_WALL_STRUCT *magicWall, SPRITES_STRUCT *sprites);

void magic_wall_draw(MAGIC_WALL_STRUCT *magicWall, SPRITES_STRUCT *sprites); 

#endif