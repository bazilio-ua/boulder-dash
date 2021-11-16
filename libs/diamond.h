#ifndef _DIAMONDH_
#define _DIAMONDH_

#include "utils.h"
#include "sprite.h"
#include "rockford.h"

typedef struct DIAMOND_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
  bool falling;
  bool redraw;
} DIAMOND_STRUCT;

DIAMOND_STRUCT *allocate_array_diamond(int diamondCount);

void diamond_init(DIAMOND_STRUCT *diamond, int pos_x, int pos_y);

void diamond_update(
    DIAMOND_STRUCT *diamond,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    ROCKFORD_STRUCT *rockford,
    long int count);

void diamond_draw(
    DIAMOND_STRUCT *diamond,
    int *diamondCount,
    SPRITES_STRUCT *sprites);

void diamond_free(DIAMOND_STRUCT *diamond);

#endif