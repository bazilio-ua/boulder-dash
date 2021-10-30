#ifndef _AMOEBAH_
#define _AMOEBAH_

#include "utils.h"
#include "sprite.h"

typedef struct AMOEBA_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
} AMOEBA_STRUCT;

void amoeba_init(AMOEBA_STRUCT *amoeba, int pos_x, int pos_y); 

void amoeba_update(AMOEBA_STRUCT *amoeba, SPRITES_STRUCT *sprites, long int count);

void amoeba_draw(AMOEBA_STRUCT *amoeba, SPRITES_STRUCT *sprites); 

#endif