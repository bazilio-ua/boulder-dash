#ifndef _EXPLOSIONH_
#define _EXPLOSIONH_

#include "utils.h"
#include "sprite.h"

typedef struct EXPLOSION_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
  int start;
  int end;
  bool redraw;
} EXPLOSION_STRUCT;

EXPLOSION_STRUCT *allocate_array_explosion();

void explosion_init(EXPLOSION_STRUCT *explosion);

void explosion_update(
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites);

void explosion_draw(EXPLOSION_STRUCT *explosion, SPRITES_STRUCT *sprites);

void explosion_free(EXPLOSION_STRUCT *explosion);

#endif