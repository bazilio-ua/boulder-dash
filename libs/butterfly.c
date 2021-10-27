#include "butterfly.h"

void butterfly_init(BUTTERFLY_STRUCT *butterfly, int pos_x, int pos_y)
{
  butterfly->x = pos_x;
  butterfly->y = pos_y;
  butterfly->source_x = BUTTERFLY_WIDTH;
  butterfly->source_y = 0;
}

void butterfly_update(BUTTERFLY_STRUCT *butterfly, SPRITES_STRUCT *sprites)
{
  butterfly->source_x += al_get_bitmap_width(sprites->butterfly) / 8;

  if (butterfly->source_x >= al_get_bitmap_width(sprites->butterfly))
    butterfly->source_x = 0;
}

void butterfly_draw(BUTTERFLY_STRUCT *butterfly, SPRITES_STRUCT *sprites)
{
  al_draw_bitmap_region(sprites->butterfly, butterfly->source_x, butterfly->source_y, BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT, butterfly->x, butterfly->y, 0);
}