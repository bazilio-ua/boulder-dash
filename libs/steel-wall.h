#ifndef _STEELWALLH_
#define _STEELWALLH_

#include "utils.h"
#include "sprite.h"
#include "rockford.h"

typedef struct STEEL_WALL_STRUCT
{
  int x, y;
  bool redraw;
} STEEL_WALL_STRUCT;

STEEL_WALL_STRUCT *allocate_array_steel_wall(int steelWallCount);

void steel_wall_init(STEEL_WALL_STRUCT *steelWall, int pos_x, int pos_y);

void steel_wall_update(
    STEEL_WALL_STRUCT *steelWall,
    int *steelWallCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT *rockford,
    long int count);

void steel_wall_draw(
    STEEL_WALL_STRUCT *steelWall,
    int *steelWallCount,
    SPRITES_STRUCT *sprites);

void steel_wall_free(STEEL_WALL_STRUCT *steelWall);

#endif