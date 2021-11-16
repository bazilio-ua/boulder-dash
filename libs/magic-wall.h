#ifndef _MAGICWALLH_
#define _MAGICWALLH_

#include "utils.h"
#include "sprite.h"
#include "boulder.h"
#include "diamond.h"

typedef struct MAGIC_WALL_STRUCT
{
    int x, y;
    int source_x;
    int source_y;
    int activeStartTime;
    bool redraw;
    bool isActive;
} MAGIC_WALL_STRUCT;

MAGIC_WALL_STRUCT *allocate_array_magic_wall(int magicWallCount);

void magic_wall_init(
    MAGIC_WALL_STRUCT *magicWall,
    int pos_x,
    int pos_y);

void magic_wall_update(
    MAGIC_WALL_STRUCT *magicWall,
    DIAMOND_STRUCT *diamond,
    int *magicWallCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    long int count);

void magic_wall_draw(
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount,
    SPRITES_STRUCT *sprites);

void magic_wall_free(MAGIC_WALL_STRUCT *magicWall);

#endif