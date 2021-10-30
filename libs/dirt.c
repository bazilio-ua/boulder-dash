#include "dirt.h"

void dirt_init(DIRT_STRUCT *dirt, int pos_x, int pos_y)
{
  dirt->x = pos_x;
  dirt->y = pos_y;
}

void dirt_update(DIRT_STRUCT *dirt, SPRITES_STRUCT *sprites, long int count)
{
  return;
}

void dirt_draw(DIRT_STRUCT *dirt, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->dirt,
      0, 0, AMOEBA_SPRITE_WIDTH, AMOEBA_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                     // color, just use white if you don't want a tint
      0, 0,                                                                          // center of rotation/scaling
      dirt->x, dirt->y,                                                          // destination
      DIRT_SCALE, DIRT_SCALE,                                                    // scale
      0, 0);
}