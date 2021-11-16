#include "amoeba.h"

AMOEBA_STRUCT *allocate_array_amoeba(int amoebaCount)
{
  return (AMOEBA_STRUCT *)calloc(amoebaCount, sizeof(AMOEBA_STRUCT));
}

void amoeba_init(
    AMOEBA_STRUCT *amoeba,
    int pos_x,
    int pos_y,
    int spawnedTime)
{
  amoeba->x = pos_x;
  amoeba->y = pos_y;
  amoeba->source_x = AMOEBA_SPRITE_WIDTH;
  amoeba->source_y = 0;
  amoeba->redraw = true;
  amoeba->spawned_time = spawnedTime;
  amoeba->last_time_grew_up = spawnedTime;
}

bool isAmoebaBlocked(AMOEBA_STRUCT *amoeba, char map[MAP_HEIGHT][MAP_WIDTH])
{
  int amoebaLine = amoeba->y / BLOCK_SIZE;
  int amoebaColumn = amoeba->x / BLOCK_SIZE;

  int topLine = amoebaLine - 1;
  int topColumn = amoebaColumn;

  int rightLine = amoebaLine;
  int rightColumn = amoebaColumn + 1;

  int bottomLine = amoebaLine + 1;
  int bottomColumn = amoebaColumn;

  int leftLine = amoebaLine;
  int leftColumn = amoebaColumn - 1;

  if (!isSpaceAmoeba(map, topLine, topColumn) &&
      !isSpaceBoulder(map, topLine, topColumn) &&
      !isSpaceSteelWall(map, topLine, topColumn) &&
      !isSpaceBrickWall(map, topLine, topColumn))
    return false;

  if (!isSpaceAmoeba(map, rightLine, rightColumn) &&
      !isSpaceBoulder(map, rightLine, rightColumn) &&
      !isSpaceSteelWall(map, rightLine, rightColumn) &&
      !isSpaceBrickWall(map, rightLine, rightColumn))
    return false;

  if (!isSpaceAmoeba(map, bottomLine, bottomColumn) &&
      !isSpaceBoulder(map, bottomLine, bottomColumn) &&
      !isSpaceSteelWall(map, bottomLine, bottomColumn) &&
      !isSpaceBrickWall(map, bottomLine, bottomColumn))
    return false;

  if (!isSpaceAmoeba(map, leftLine, leftColumn) &&
      !isSpaceBoulder(map, leftLine, leftColumn) &&
      !isSpaceSteelWall(map, leftLine, leftColumn) &&
      !isSpaceBrickWall(map, leftLine, leftColumn))
    return false;

  return true;
}

void amoeba_update(
    AMOEBA_STRUCT *amoeba,
    BOULDER_STRUCT *boulder,
    DIAMOND_STRUCT *diamond,
    int *amoebaCount,
    int *boulderCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    long int count)
{
  AMOEBA_STRUCT *amoebaPtr;
  bool isBlocked = true;
  int i, j, k;

  for (i = 0; i < *amoebaCount; i++)
  {
    amoebaPtr = &amoeba[i];

    if (amoebaPtr->redraw)
    {
      if (isSpaceEmpty(map, amoebaPtr->y / BLOCK_SIZE, amoebaPtr->x / BLOCK_SIZE))
      {
        amoebaPtr->redraw = false;
        return;
      }

      if (!isSpaceAmoeba(map, (amoebaPtr->y / BLOCK_SIZE), (amoebaPtr->x / BLOCK_SIZE)))
      {
        int amoebaPtrLine = amoebaPtr->y / BLOCK_SIZE;
        int amoebaPtrColumn = amoebaPtr->x / BLOCK_SIZE;

        EXPLOSION_STRUCT *explosionPtr;
        int explosionCount = 0;

        for (j = amoebaPtrLine - 1; j <= amoebaPtrLine + 1; j++)
        {
          for (k = amoebaPtrColumn - 1; k <= amoebaPtrColumn + 1; k++)
          {
            if (!isSpaceSteelWall(map, j, k))
            {
              update_map_state(map, IS_EMPTY, j, k);

              explosionPtr = &explosion[explosionCount];

              explosionPtr->x = k * BLOCK_SIZE;
              explosionPtr->y = j * BLOCK_SIZE;
              explosionPtr->redraw = true;
              explosionPtr->start = 0;
              explosionPtr->end = EXPLOSION_DURATION;

              explosionCount++;
            }
          }
        }

        amoebaPtr->redraw = false;

        return;
      }

      if (isBlocked)
        isBlocked = isAmoebaBlocked(amoebaPtr, map);

      if (count % 5 == 0)
      {

        amoebaPtr->source_x += al_get_bitmap_width(sprites->amoeba) / 8;

        if (amoebaPtr->source_x >= al_get_bitmap_width(sprites->amoeba))
          amoebaPtr->source_x = 0;
      }

      if (count - amoebaPtr->last_time_grew_up >= TIME_TO_GROW)
      {
        int dirtLine = -1;
        int dirtColumn = -1;
        AMOEBA_STRUCT *amoebaTemp = &amoeba[*amoebaCount];

        amoebaPtr->last_time_grew_up = count;

        if (isSpaceDirt(map, amoebaPtr->y / BLOCK_SIZE - 1, amoebaPtr->x / BLOCK_SIZE))
        {
          dirtLine = amoebaPtr->y / BLOCK_SIZE - 1;
          dirtColumn = amoebaPtr->x / BLOCK_SIZE;
        }
        else if (isSpaceDirt(map, amoebaPtr->y / BLOCK_SIZE, amoebaPtr->x / BLOCK_SIZE + 1))
        {
          dirtLine = amoebaPtr->y / BLOCK_SIZE;
          dirtColumn = amoebaPtr->x / BLOCK_SIZE + 1;
        }
        else if (isSpaceDirt(map, amoebaPtr->y / BLOCK_SIZE + 1, amoebaPtr->x / BLOCK_SIZE))
        {
          dirtLine = amoebaPtr->y / BLOCK_SIZE + 1;
          dirtColumn = amoebaPtr->x / BLOCK_SIZE;
        }
        else if (isSpaceDirt(map, amoebaPtr->y / BLOCK_SIZE, amoebaPtr->x / BLOCK_SIZE - 1))
        {
          dirtLine = amoebaPtr->y / BLOCK_SIZE;
          dirtColumn = amoebaPtr->x / BLOCK_SIZE - 1;
        }

        if (dirtLine != -1 && dirtColumn != -1)
        {
          (*amoebaCount)++;
          update_map_state(map, IS_AMOEBA, dirtLine, dirtColumn);

          amoebaTemp->x = dirtColumn * BLOCK_SIZE;
          amoebaTemp->y = dirtLine * BLOCK_SIZE;
          amoebaTemp->redraw = true;
          amoebaTemp->source_x = AMOEBA_SPRITE_WIDTH;
          amoebaTemp->source_y = 0;
          amoebaTemp->last_time_grew_up = count;
        }
      }
    }
  }

  if (count - amoeba[0].spawned_time >= AMOEBA_LIFE_TIME)
  {
    BOULDER_STRUCT *boulderTemp;

    for (i = 0; i < *amoebaCount; i++)
    {
      amoebaPtr = &amoeba[i];

      if (amoebaPtr->redraw)
      {
        boulderTemp = &boulder[*boulderCount];

        int amoebaLine = amoebaPtr->y / BLOCK_SIZE;
        int amoebaColumn = amoebaPtr->x / BLOCK_SIZE;

        (*boulderCount)++;
        update_map_state(map, IS_BOULDER, amoebaLine, amoebaColumn);

        boulderTemp->x = amoebaColumn * BLOCK_SIZE;
        boulderTemp->y = amoebaLine * BLOCK_SIZE;
        boulderTemp->collision_time = 0;
        boulderTemp->redraw = true;
        boulderTemp->falling = false;

        amoebaPtr->redraw = false;
      }
    }
  }

  else if (isBlocked)
  {
    DIAMOND_STRUCT *diamondTemp;

    for (i = 0; i < *amoebaCount; i++)
    {
      amoebaPtr = &amoeba[i];

      if (amoebaPtr->redraw)
      {
        diamondTemp = &diamond[*diamondCount];

        int amoebaLine = amoebaPtr->y / BLOCK_SIZE;
        int amoebaColumn = amoebaPtr->x / BLOCK_SIZE;

        (*diamondCount)++;
        update_map_state(map, IS_DIAMOND, amoebaLine, amoebaColumn);

        diamondTemp->x = amoebaColumn * BLOCK_SIZE;
        diamondTemp->y = amoebaLine * BLOCK_SIZE;
        diamondTemp->source_x = DIAMOND_SPRITE_WIDTH;
        diamondTemp->source_y = 0;
        diamondTemp->redraw = true;
        diamondTemp->falling = false;

        amoebaPtr->redraw = false;
      }
    }
  }
}

void amoeba_draw(
    AMOEBA_STRUCT *amoeba,
    int *amoebaCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *amoebaCount; i++)
    if (amoeba[i].redraw)
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->amoeba,
          amoeba[i].source_x, amoeba[i].source_y, AMOEBA_SPRITE_WIDTH, AMOEBA_SPRITE_HEIGHT, // source bitmap region
          al_map_rgb(255, 255, 255),                                                         // color, just use white if you don't want a tint
          0, 0,                                                                              // center of rotation/scaling
          amoeba[i].x, amoeba[i].y,                                                          // destination
          AMOEBA_SCALE, AMOEBA_SCALE,                                                        // scale
          0, 0);
}

void amoeba_free(AMOEBA_STRUCT *amoeba)
{
  free(amoeba);
}