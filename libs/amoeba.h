#ifndef _AMOEBAH_
#define _AMOEBAH_

#include "utils.h"
#include "sprite.h"
#include "explosion.h"

typedef struct AMOEBA_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
  bool redraw;
} AMOEBA_STRUCT;

AMOEBA_STRUCT *allocate_array_amoeba(int amoebaCount);

void amoeba_init(AMOEBA_STRUCT *amoeba, int pos_x, int pos_y);

void amoeba_update(
    AMOEBA_STRUCT *amoeba,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    long int count);

void amoeba_draw(AMOEBA_STRUCT *amoeba, SPRITES_STRUCT *sprites);

void amoeba_free(AMOEBA_STRUCT *amoeba);

#endif