#ifndef _EXITH_
#define _EXITH_

#include "utils.h"
#include "sprite.h"

typedef struct EXIT_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
} EXIT_STRUCT;

void exit_init(EXIT_STRUCT *exit, int pos_x, int pos_y); 

void exit_update(EXIT_STRUCT *exit, SPRITES_STRUCT *sprites);

void exit_draw(EXIT_STRUCT *exit, SPRITES_STRUCT *sprites); 

#endif