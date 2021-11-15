#ifndef _BUTTERFLYH_
#define _BUTTERFLYH_

#include "utils.h"
#include "sprite.h"
#include "explosion.h"
#include "diamond.h"

typedef struct BUTTERFLY_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
  int direction;
  int amount_of_diamonds;
  bool redraw;
} BUTTERFLY_STRUCT;

BUTTERFLY_STRUCT *allocate_array_butterfly(int butterflyCount);

void butterfly_init(
    BUTTERFLY_STRUCT *butterfly,
    int pos_x,
    int pos_y);

void butterfly_update(
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *butterflyCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    long int count);

void butterfly_draw(
    BUTTERFLY_STRUCT *butterfly,
    SPRITES_STRUCT *sprites);

void butterfly_free(BUTTERFLY_STRUCT *butterfly);

#endif