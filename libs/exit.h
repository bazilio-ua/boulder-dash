#ifndef _EXITH_
#define _EXITH_

#include "utils.h"
#include "sprite.h"
#include "rockford.h"

typedef struct EXIT_STRUCT
{
  int x, y;
  int source_x;
  int source_y;
  bool redraw;
} EXIT_STRUCT;

EXIT_STRUCT *allocate_exit();

void exit_init(
    EXIT_STRUCT *exit,
    int pos_x,
    int pos_y);

void exit_update(
    EXIT_STRUCT *exit,
    ROCKFORD_STRUCT *rockford,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    long int count);

void exit_draw(
    EXIT_STRUCT *exit,
    SPRITES_STRUCT *sprites);

void exit_free(EXIT_STRUCT *exit);

#endif