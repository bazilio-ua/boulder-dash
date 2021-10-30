#include "amoeba.h"

void amoeba_init(AMOEBA_STRUCT *amoeba, int pos_x, int pos_y)
{
  amoeba->x = pos_x;
  amoeba->y = pos_y;
  amoeba->source_x = AMOEBA_SPRITE_WIDTH;
  amoeba->source_y = 0;
}

void amoeba_update(AMOEBA_STRUCT *amoeba, SPRITES_STRUCT *sprites, long int count)
{
  if (count % 5 == 0)
  {

    amoeba->source_x += al_get_bitmap_width(sprites->amoeba) / 8;

    if (amoeba->source_x >= al_get_bitmap_width(sprites->amoeba))
      amoeba->source_x = 0;
  }
}

void amoeba_draw(AMOEBA_STRUCT *amoeba, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->amoeba,
      amoeba->source_x, amoeba->source_y, AMOEBA_SPRITE_WIDTH, AMOEBA_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                     // color, just use white if you don't want a tint
      0, 0,                                                                          // center of rotation/scaling
      amoeba->x, amoeba->y,                                                          // destination
      AMOEBA_SCALE, AMOEBA_SCALE,                                                    // scale
      0, 0);
}