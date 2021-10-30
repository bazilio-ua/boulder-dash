#include "butterfly.h"

void butterfly_init(BUTTERFLY_STRUCT *butterfly, int pos_x, int pos_y)
{
  butterfly->x = pos_x;
  butterfly->y = pos_y;
  butterfly->source_x = BUTTERFLY_SPRITE_WIDTH;
  butterfly->source_y = 0;
}

void butterfly_update(BUTTERFLY_STRUCT *butterfly, SPRITES_STRUCT *sprites, long int count)
{
  if (count % 5 == 0)
  {
    butterfly->source_x += al_get_bitmap_width(sprites->butterfly) / 8;

    if (butterfly->source_x >= al_get_bitmap_width(sprites->butterfly))
      butterfly->source_x = 0;
  }
}

void butterfly_draw(BUTTERFLY_STRUCT *butterfly, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->butterfly,
      butterfly->source_x, butterfly->source_y, BUTTERFLY_SPRITE_WIDTH, BUTTERFLY_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                 // color, just use white if you don't want a tint
      0, 0,                                                                                      // center of rotation/scaling
      butterfly->x, butterfly->y,                                                                // destination
      BUTTERFLY_SCALE, BUTTERFLY_SCALE,                                                          // scale
      0, 0);
}