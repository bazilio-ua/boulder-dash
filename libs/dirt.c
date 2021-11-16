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

void dirt_update(
    DIRT_STRUCT *dirt,
    int *dirtCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT *rockford,
    long int count)
{
  DIRT_STRUCT *dirtPtr;

  for (int i = 0; i < *dirtCount; i++)
  {
    dirtPtr = &dirt[i];

    if (dirtPtr->redraw)
    {
      if (!isSpaceDirt(map, dirtPtr->y / BLOCK_SIZE, dirtPtr->x / BLOCK_SIZE))
      {
        dirtPtr->redraw = false;
        return;
      }

      if (count % 5 == 0)
        if (isCollision(dirtPtr->x, dirtPtr->y, rockford->x, rockford->y))
          dirtPtr->redraw = false;
    }
  }
}

void dirt_draw(
    DIRT_STRUCT *dirt,
    int *dirtCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *dirtCount; i++)
    if (dirt[i].redraw)
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->dirt,
          0, 0, AMOEBA_SPRITE_WIDTH, AMOEBA_SPRITE_HEIGHT, // source bitmap region
          al_map_rgb(255, 255, 255),                       // color, just use white if you don't want a tint
          0, 0,                                            // center of rotation/scaling
          dirt[i].x, dirt[i].y,                            // destination
          DIRT_SCALE, DIRT_SCALE,                          // scale
          0, 0);
}

void dirt_free(DIRT_STRUCT *dirt)
{
  free(dirt);
}