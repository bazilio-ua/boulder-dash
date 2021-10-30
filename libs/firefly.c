#include "firefly.h"

void firefly_init(FIREFLY_STRUCT *firefly, int pos_x, int pos_y)
{
  firefly->x = pos_x;
  firefly->y = pos_y;
  firefly->source_x = FIREFLY_SPRITE_WIDTH;
  firefly->source_y = 0;
}

void firefly_update(FIREFLY_STRUCT *firefly, SPRITES_STRUCT *sprites, long int count)
{
  if (count % 5 == 0)
  {
    firefly->source_x += al_get_bitmap_width(sprites->firefly) / 8;

    if (firefly->source_x >= al_get_bitmap_width(sprites->firefly))
      firefly->source_x = 0;
  }
}

void firefly_draw(FIREFLY_STRUCT *firefly, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->firefly,
      firefly->source_x, firefly->source_y, FIREFLY_SPRITE_WIDTH, FIREFLY_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                     // color, just use white if you don't want a tint
      0, 0,                                                                          // center of rotation/scaling
      firefly->x, firefly->y,                                                          // destination
      FIREFLY_SCALE, FIREFLY_SCALE,                                                    // scale
      0, 0);
}