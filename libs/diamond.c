#include "diamond.h"

void diamond_init(DIAMOND_STRUCT *diamond, int pos_x, int pos_y)
{
  diamond->x = pos_x;
  diamond->y = pos_y;
  diamond->source_x = DIAMOND_WIDTH;
  diamond->source_y = 0;
}

void diamond_update(DIAMOND_STRUCT *diamond, SPRITES_STRUCT *sprites)
{
  diamond->source_x += al_get_bitmap_width(sprites->diamond) / 8;

  if (diamond->source_x >= al_get_bitmap_width(sprites->diamond))
    diamond->source_x = 0;
}

void diamond_draw(DIAMOND_STRUCT *diamond, SPRITES_STRUCT *sprites)
{
  al_draw_bitmap_region(sprites->diamond, diamond->source_x, diamond->source_y, DIAMOND_WIDTH, DIAMOND_HEIGHT, diamond->x, diamond->y, 0);
}