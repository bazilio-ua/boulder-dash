#include "dirt.h"

DIRT_STRUCT *allocate_array_dirt(int dirtCount)
{
  return (DIRT_STRUCT *)malloc(sizeof(DIRT_STRUCT) * dirtCount);
}

void dirt_init(DIRT_STRUCT *dirt, int pos_x, int pos_y)
{
  dirt->x = pos_x;
  dirt->y = pos_y;
  dirt->redraw = true;
}

void dirt_update(DIRT_STRUCT *dirt, ROCKFORD_STRUCT *rockford, long int count)
{
  if (count % 5 == 0)
    if (isCollision(dirt->x, dirt->y, rockford->x, rockford->y) && dirt->redraw)
      dirt->redraw = false;
}

void dirt_draw(DIRT_STRUCT *dirt, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->dirt,
      0, 0, AMOEBA_SPRITE_WIDTH, AMOEBA_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                       // color, just use white if you don't want a tint
      0, 0,                                            // center of rotation/scaling
      dirt->x, dirt->y,                                // destination
      DIRT_SCALE, DIRT_SCALE,                          // scale
      0, 0);
}

void dirt_free(DIRT_STRUCT *dirt)
{
  free(dirt);
}