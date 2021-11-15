#ifndef _FIREFLYH_
#define _FIREFLYH_

#include "utils.h"
#include "sprite.h"
#include "explosion.h"

typedef struct FIREFLY_STRUCT
{
  int x, y;
  int direction;
  int source_x;
  int source_y;
  bool redraw;
} FIREFLY_STRUCT;

FIREFLY_STRUCT *allocate_array_firefly(int fireflyCount);

void firefly_init(FIREFLY_STRUCT *firefly, int pos_x, int pos_y);

void firefly_update(
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    long int count);

void firefly_draw(FIREFLY_STRUCT *firefly, SPRITES_STRUCT *sprites);

void firefly_free(FIREFLY_STRUCT *firefly);

#endif