#ifndef _BRICKWALLH_
#define _BRICKWALLH_

#include "utils.h"
#include "sprite.h"
#include "rockford.h"

typedef struct BRICK_WALL_STRUCT
{
  int x, y;
  bool redraw;
} BRICK_WALL_STRUCT;

BRICK_WALL_STRUCT *allocate_array_brick_wall(int brickWallCount);

void brick_wall_init(BRICK_WALL_STRUCT *brickWall, int pos_x, int pos_y);

void brick_wall_update(
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT *rockford,
    long int count);

void brick_wall_draw(
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    SPRITES_STRUCT *sprites);

void brick_wall_free(BRICK_WALL_STRUCT *steelWall);

#endif