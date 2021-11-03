#ifndef _SPRITEH_
#define _SPRITEH_

#include "utils.h"

typedef struct SPRITES_STRUCT
{
  ALLEGRO_BITMAP *_sheet;
  ALLEGRO_BITMAP *rockford;
  ALLEGRO_BITMAP *rockford_running_left;
  ALLEGRO_BITMAP *rockford_running_right;
  ALLEGRO_BITMAP *rockford_waiting;

  ALLEGRO_BITMAP *diamond;

  ALLEGRO_BITMAP *firefly;

  ALLEGRO_BITMAP *amoeba;

  ALLEGRO_BITMAP *butterfly;

  ALLEGRO_BITMAP *exit;

  ALLEGRO_BITMAP *magic_wall;

  ALLEGRO_BITMAP *steel_wall;

  ALLEGRO_BITMAP *brick_wall;

  ALLEGRO_BITMAP *boulder;

  ALLEGRO_BITMAP *dirt;
} SPRITES_STRUCT;

void sprites_init(SPRITES_STRUCT *sprites); 

void sprites_deinit(SPRITES_STRUCT *sprites);

#endif