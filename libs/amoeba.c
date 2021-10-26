#include "amoeba.h"

void amoeba_init(AMOEBA_STRUCT *amoeba, int pos_x, int pos_y)
{
  amoeba->x = pos_x;
  amoeba->y = pos_y;
  amoeba->source_x = AMOEBA_WIDTH;
  amoeba->source_y = 0;
}

void amoeba_update(AMOEBA_STRUCT *amoeba, SPRITES_STRUCT *sprites)
{
  amoeba->source_x += al_get_bitmap_width(sprites->amoeba) / 8;

  if (amoeba->source_x >= al_get_bitmap_width(sprites->amoeba))
    amoeba->source_x = 0;
}

void amoeba_draw(AMOEBA_STRUCT *amoeba, SPRITES_STRUCT *sprites)
{
  al_draw_bitmap_region(sprites->amoeba, amoeba->source_x, amoeba->source_y, AMOEBA_WIDTH, AMOEBA_HEIGHT, amoeba->x, amoeba->y, 0);
}