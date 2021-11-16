#ifndef _BOULDERH_
#define _BOULDERH_

#include "utils.h"
#include "sprite.h"
#include "rockford.h"
#include "diamond.h"

typedef struct BOULDER_STRUCT
{
  int x, y;
  long int collision_time;
  bool falling;
  bool redraw;
} BOULDER_STRUCT;

BOULDER_STRUCT *allocate_array_boulder(int boulderCount);

void boulder_init(BOULDER_STRUCT *boulder, int pos_x, int pos_y);

void boulder_update(
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT *rockford,
    long int count);

void boulder_draw(
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    SPRITES_STRUCT *sprites);

void boulder_free(BOULDER_STRUCT *steelWall);

#endif