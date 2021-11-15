#include "boulder.h"

BOULDER_STRUCT *allocate_array_boulder(int boulderCount)
{
  return (BOULDER_STRUCT *)malloc(sizeof(BOULDER_STRUCT) * boulderCount);
}

void boulder_init(BOULDER_STRUCT *boulder, int pos_x, int pos_y)
{
  boulder->x = pos_x;
  boulder->y = pos_y;
  boulder->collision_time = 0;
  boulder->redraw = true;
  boulder->falling = false;
}

void boulder_update(
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT *rockford,
    long int count)
{
  BOULDER_STRUCT *boulderPtr;

  for (int i = 0; i < *boulderCount; i++)
  {
    boulderPtr = &boulder[i];

    if (boulderPtr->redraw)
    {
      if (!isSpaceBoulder(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE))
      {
        boulderPtr->redraw = false;
        return;
      }

      if (count % 5 == 0)
      {
        if (boulderPtr->falling &&
            (isSpaceRockford(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||
             isSpaceFirefly(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||
             isSpaceButterfly(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->y += BLOCK_SIZE;
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          return;
        }

        boulderPtr->falling = false;

        if (isSpaceEmpty(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE))
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->y += BLOCK_SIZE;
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->falling = true;
        }
        else if (
            isSpaceMagicWall(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) &&
            isSpaceEmpty(map, boulderPtr->y / BLOCK_SIZE + 2, boulderPtr->x / BLOCK_SIZE))
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->y += BLOCK_SIZE;
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->falling = true;
        }
        else if (
            isSpaceEmpty(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE - 1) &&
            isSpaceEmpty(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE - 1) &&
            (isSpaceBoulder(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||
             isSpaceBrickWall(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||
             isSpaceDiamond(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->x -= BLOCK_SIZE;
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
        }
        else if (
            isSpaceEmpty(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE + 1) &&
            isSpaceEmpty(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE + 1) &&
            (isSpaceBoulder(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||
             isSpaceBrickWall(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||
             isSpaceDiamond(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->x += BLOCK_SIZE;
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
        }
        else if (
            isSpaceRockford(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE + 1) &&
            rockford->active && rockford->direction == LEFT)
        {

          if (!boulderPtr->collision_time)
            boulderPtr->collision_time = count;

          if (count - boulderPtr->collision_time == 60) //1s
          {
            update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
            update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);

            rockford->x -= ROCKFORD_SPEED;
            boulderPtr->x -= ROCKFORD_SPEED;

            if (map[boulderPtr->y / BLOCK_SIZE][boulderPtr->x / BLOCK_SIZE] != IS_EMPTY)
            {
              rockford->x += ROCKFORD_SPEED;
              boulderPtr->x += ROCKFORD_SPEED;
            }

            boulderPtr->collision_time = count;
          }

          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        }

        else if (
            isSpaceRockford(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE - 1) &&
            rockford->active && rockford->direction == RIGHT)
        {

          if (!boulderPtr->collision_time)
            boulderPtr->collision_time = count;

          if (count - boulderPtr->collision_time == 60) //1s
          {
            update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
            update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);

            rockford->x += ROCKFORD_SPEED;
            boulderPtr->x += ROCKFORD_SPEED;

            if (map[boulderPtr->y / BLOCK_SIZE][boulderPtr->x / BLOCK_SIZE] != IS_EMPTY)
            {
              rockford->x -= ROCKFORD_SPEED;
              boulderPtr->x -= ROCKFORD_SPEED;
            }

            boulderPtr->collision_time = count;
          }

          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        }
        else
          boulderPtr->collision_time = 0;
      }
    }
  }
}

void boulder_draw(BOULDER_STRUCT *boulder, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->boulder,
      0, 0, BOULDER_SPRITE_WIDTH, BOULDER_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                         // color, just use white if you don't want a tint
      0, 0,                                              // center of rotation/scaling
      boulder->x, boulder->y,                            // destination
      BOULDER_SCALE, BOULDER_SCALE,                      // scale
      0, 0);
}

void boulder_free(BOULDER_STRUCT *boulder)
{
  free(boulder);
}