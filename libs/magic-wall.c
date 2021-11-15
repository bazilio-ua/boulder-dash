#include "magic-wall.h"

MAGIC_WALL_STRUCT *allocate_array_magic_wall(int magicWallCount)
{
  return (MAGIC_WALL_STRUCT *)malloc(sizeof(MAGIC_WALL_STRUCT) * magicWallCount);
}

void magic_wall_init(MAGIC_WALL_STRUCT *magicWall, int pos_x, int pos_y)
{
  magicWall->x = pos_x;
  magicWall->y = pos_y;
  magicWall->source_x = 0;
  magicWall->source_y = 0;
  magicWall->redraw = true;
  magicWall->isActive = false;
  magicWall->activeStartTime = 0;
}

void active_all_magic_walls(
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount,
    int startTime)
{
  MAGIC_WALL_STRUCT *magicWallPtr;

  for (int i = 0; i < *magicWallCount; i++)
  {
    magicWallPtr = &magicWall[i];

    magicWallPtr->isActive = true,
    magicWallPtr->activeStartTime = startTime;
  }
}

void desactive_all_magic_walls(
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount)
{
  MAGIC_WALL_STRUCT *magicWallPtr;

  for (int i = 0; i < *magicWallCount; i++)
  {
    magicWallPtr = &magicWall[i];

    magicWallPtr->isActive = false;
    magicWallPtr->source_x = 0;
    magicWallPtr->activeStartTime = 0;
  }
}

void magic_wall_update(
    MAGIC_WALL_STRUCT *magicWall,
    DIAMOND_STRUCT *diamond,
    int *magicWallCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    long int count)
{
  MAGIC_WALL_STRUCT *magicWallPtr;

  for (int i = 0; i < *magicWallCount; i++)
  {
    magicWallPtr = &magicWall[i];

    if (magicWallPtr->redraw)
    {
      if (isSpaceBoulder(map, magicWallPtr->y / BLOCK_SIZE, magicWallPtr->x / BLOCK_SIZE))
      {
        DIAMOND_STRUCT *diamondTemp;

        update_map_state(map, IS_MAGIC_WALL, magicWallPtr->y / BLOCK_SIZE, magicWallPtr->x / BLOCK_SIZE);
        active_all_magic_walls(magicWall, magicWallCount, count);

        diamondTemp = &diamond[*diamondCount];

        int magicWallLine = magicWallPtr->y / BLOCK_SIZE + 1;
        int magicWallColum = magicWallPtr->x / BLOCK_SIZE;

        (*diamondCount)++;
        update_map_state(map, IS_DIAMOND, magicWallLine, magicWallColum);

        diamondTemp->x = magicWallColum * BLOCK_SIZE;
        diamondTemp->y = magicWallLine * BLOCK_SIZE;
        diamondTemp->source_x = DIAMOND_SPRITE_WIDTH;
        diamondTemp->source_y = 0;
        diamondTemp->redraw = true;
        diamondTemp->falling = false;

        return;
      }

      if (!isSpaceMagicWall(map, magicWallPtr->y / BLOCK_SIZE, magicWallPtr->x / BLOCK_SIZE))
      {
        magicWallPtr->redraw = false;
        return;
      }

      if (count % 5 == 0)
      {
        if (magicWallPtr->isActive)
        {
          magicWallPtr->source_x += al_get_bitmap_width(sprites->magic_wall) / 5;

          if (count - magicWall->activeStartTime >= ACTIVE_DURATION)
            desactive_all_magic_walls(magicWall, magicWallCount);
        }

        if (magicWallPtr->source_x >= al_get_bitmap_width(sprites->magic_wall))
          magicWallPtr->source_x = 0;
      }
    }
  }
}

void magic_wall_draw(MAGIC_WALL_STRUCT *magicWall, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->magic_wall,
      magicWall->source_x, magicWall->source_y, MAGIC_WALL_SPRITE_WIDTH, MAGIC_WALL_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                   // color, just use white if you don't want a tint
      0, 0,                                                                                        // center of rotation/scaling
      magicWall->x, magicWall->y,                                                                  // destination
      MAGIC_WALL_SCALE, MAGIC_WALL_SCALE,                                                          // scale
      0, 0);
}

void magic_wall_free(MAGIC_WALL_STRUCT *magicWall)
{
  free(magicWall);
}