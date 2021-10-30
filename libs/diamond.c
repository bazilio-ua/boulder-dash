#include "diamond.h"

void diamond_init(DIAMOND_STRUCT *diamond, int pos_x, int pos_y)
{
  diamond->x = pos_x;
  diamond->y = pos_y;
  diamond->source_x = DIAMOND_SPRITE_WIDTH;
  diamond->source_y = 0;
}

void diamond_update(
    DIAMOND_STRUCT *diamond,
    SPRITES_STRUCT *sprites,
    ROCKFORD_STRUCT *rockford,
    long int count)
{
  if (count % 5 == 0)
  {
    diamond->source_x += al_get_bitmap_width(sprites->diamond) / 8;

    if (diamond->source_x >= al_get_bitmap_width(sprites->diamond))
      diamond->source_x = 0;
  }

  if (isCollision(diamond->x, diamond->y, rockford->x, rockford->y))
  {
    rockford->quantity_of_diamonds++;
    rockford->score += DIAMOND_SCORE;
    diamond->x = -100;
    diamond->y = -100;
  }
}

void diamond_draw(DIAMOND_STRUCT *diamond, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->diamond,
      diamond->source_x, diamond->source_y, DIAMOND_SPRITE_WIDTH, DIAMOND_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                         // color, just use white if you don't want a tint
      0, 0,                                                                              // center of rotation/scaling
      diamond->x, diamond->y,                                                            // destination
      DIAMOND_SCALE, DIAMOND_SCALE,                                                      // scale
      0, 0);
  // al_draw_bitmap_region(sprites->diamond, diamond->source_x, diamond->source_y, DIAMOND_SPRITE_WIDTH, DIAM, diamond->x, diamond->y, 0);
}