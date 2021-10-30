#include "exit.h"

void exit_init(EXIT_STRUCT *exit, int pos_x, int pos_y)
{
  exit->x = pos_x;
  exit->y = pos_y;
  exit->source_x = EXIT_SPRITE_WIDTH;
  exit->source_y = 0;
}

void exit_update(EXIT_STRUCT *exit, SPRITES_STRUCT *sprites, long int count)
{
  if (count % 5 == 0)
  {
    exit->source_x += al_get_bitmap_width(sprites->exit) / 3;

    if (exit->source_x >= al_get_bitmap_width(sprites->exit))
      exit->source_x = 0;
  }
}

void exit_draw(EXIT_STRUCT *exit, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->exit,
      exit->source_x, exit->source_y, EXIT_SPRITE_WIDTH, EXIT_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                             // color, just use white if you don't want a tint
      0, 0,                                                                  // center of rotation/scaling
      exit->x, exit->y,                                                  // destination
      EXIT_SCALE, EXIT_SCALE,                                            // scale
      0, 0);
}