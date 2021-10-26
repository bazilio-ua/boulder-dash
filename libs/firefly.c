#include "firefly.h"

void firefly_init(FIREFLY_STRUCT *firefly, int pos_x, int pos_y)
{
  firefly->x = pos_x;
  firefly->y = pos_y;
  firefly->source_x = FIREFLY_WIDTH;
  firefly->source_y = 0;
}

void firefly_update(FIREFLY_STRUCT *firefly, SPRITES_STRUCT *sprites)
{
  firefly->source_x += al_get_bitmap_width(sprites->firefly) / 8;

  if (firefly->source_x >= al_get_bitmap_width(sprites->firefly))
    firefly->source_x = 0;
}

void firefly_draw(FIREFLY_STRUCT *firefly, SPRITES_STRUCT *sprites)
{
  al_draw_bitmap_region(sprites->firefly, firefly->source_x, firefly->source_y, FIREFLY_WIDTH, FIREFLY_HEIGHT, firefly->x, firefly->y, 0);
}