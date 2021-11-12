#include "amoeba.h"

AMOEBA_STRUCT *allocate_array_amoeba(int amoebaCount)
{
  return (AMOEBA_STRUCT *)malloc(sizeof(AMOEBA_STRUCT) * amoebaCount);
}

void amoeba_init(AMOEBA_STRUCT *amoeba, int pos_x, int pos_y)
{
  amoeba->x = pos_x;
  amoeba->y = pos_y;
  amoeba->source_x = AMOEBA_SPRITE_WIDTH;
  amoeba->source_y = 0;
  amoeba->redraw = true;
}

void amoeba_update(
    AMOEBA_STRUCT *amoeba,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    long int count)
{

  if (isSpaceEmpty(map, amoeba->y / BLOCK_SIZE, amoeba->x / BLOCK_SIZE))
  {
    amoeba->redraw = false;
    return;
  }

  else if (!isSpaceAmoeba(map, (amoeba->y / BLOCK_SIZE), (amoeba->x / BLOCK_SIZE)))
  {
    int amoebaLine = amoeba->y / BLOCK_SIZE;
    int amoebaColumn = amoeba->x / BLOCK_SIZE;

    EXPLOSION_STRUCT *explosionPtr;
    int explosionCount = 0;

    for (int i = amoebaLine - 1; i <= amoebaLine + 1; i++)
      for (int j = amoebaColumn - 1; j <= amoebaColumn + 1; j++)
        if (!isSpaceSteelWall(map, i, j))
        {
          update_map_state(map, IS_EMPTY, i, j);

          explosionPtr = &explosion[explosionCount];

          explosionPtr->x = j * BLOCK_SIZE;
          explosionPtr->y = i * BLOCK_SIZE;
          explosionPtr->redraw = true;
          explosionPtr->start = 0;
          explosionPtr->end = EXPLOSION_DURATION;

          explosionCount++;
        }

    amoeba->redraw = false;

    return;
  }

  else if (count % 5 == 0)
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

void amoeba_free(AMOEBA_STRUCT *amoeba)
{
  free(amoeba);
}