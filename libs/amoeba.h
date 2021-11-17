#ifndef _AMOEBAH_
#define _AMOEBAH_

#include "utils.h"
#include "sprite.h"
#include "boulder.h"
#include "explosion.h"
#include "diamond.h"
#include "audio.h"

typedef struct AMOEBA_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
  int spawned_time;
  int last_time_grew_up;
  bool redraw;
} AMOEBA_STRUCT;

AMOEBA_STRUCT *allocate_array_amoeba(int amoebaCount);

void amoeba_init(
    AMOEBA_STRUCT *amoeba,
    int pos_x,
    int pos_y,
    int spawnedTime);

void amoeba_update(
    AMOEBA_STRUCT *amoeba,
    BOULDER_STRUCT *boulder,
    DIAMOND_STRUCT *diamond,
    int *amoebaCount,
    int *boulderCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    SPRITES_STRUCT *sprites,
    long int count);

void amoeba_draw(
    AMOEBA_STRUCT *amoeba,
    int *amoebaCount,
    SPRITES_STRUCT *sprites);

void amoeba_free(AMOEBA_STRUCT *amoeba);

#endif