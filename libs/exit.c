#include "exit.h"

void exit_init(EXIT_STRUCT *exit, int pos_x, int pos_y)
{
  exit->x = pos_x;
  exit->y = pos_y;
  exit->source_x = EXIT_WIDTH;
  exit->source_y = 0;
}

void exit_update(EXIT_STRUCT *exit, SPRITES_STRUCT *sprites)
{
  exit->source_x += al_get_bitmap_width(sprites->exit) / 3;

  if (exit->source_x >= al_get_bitmap_width(sprites->exit))
    exit->source_x = 0;
}

void exit_draw(EXIT_STRUCT *exit, SPRITES_STRUCT *sprites)
{
  al_draw_bitmap_region(sprites->exit, exit->source_x, exit->source_y, EXIT_WIDTH, EXIT_HEIGHT, exit->x, exit->y, 0);
}