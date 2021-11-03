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
}

void boulder_update(
    BOULDER_STRUCT *boulder,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT *rockford,
    long int count)
{
  if (count % 5 == 0)
  {
    if (map[boulder->y / BLOCK_SIZE + 1][boulder->x / BLOCK_SIZE] == IS_EMPTY)
    {
      update_map_state(map, IS_EMPTY, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
      boulder->y += BLOCK_SIZE;
      update_map_state(map, IS_BOULDER, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
    }
    else if (
        map[boulder->y / BLOCK_SIZE + 1][boulder->x / BLOCK_SIZE - 1] == IS_EMPTY &&
        map[boulder->y / BLOCK_SIZE][boulder->x / BLOCK_SIZE - 1] == IS_EMPTY && 
        map[boulder->y / BLOCK_SIZE + 1][boulder->x / BLOCK_SIZE] == IS_BOULDER)
    {
      update_map_state(map, IS_EMPTY, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
      boulder->x -= BLOCK_SIZE;
      update_map_state(map, IS_BOULDER, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
    }
    else if (
        map[boulder->y / BLOCK_SIZE + 1][boulder->x / BLOCK_SIZE + 1] == IS_EMPTY &&
        map[boulder->y / BLOCK_SIZE][boulder->x / BLOCK_SIZE + 1] == IS_EMPTY && 
        map[boulder->y / BLOCK_SIZE + 1][boulder->x / BLOCK_SIZE] == IS_BOULDER)
    {
      update_map_state(map, IS_EMPTY, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
      boulder->x += BLOCK_SIZE;
      update_map_state(map, IS_BOULDER, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
    }
    else if (isCollision(boulder->x, boulder->y, rockford->x, rockford->y))
    {
      if (!boulder->collision_time)
        boulder->collision_time = count;
      switch (rockford->direction)
      {
      case UP:
        rockford->y += ROCKFORD_SPEED;
        update_map_state(map, IS_BOULDER, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        break;
      case DOWN:
        rockford->y -= ROCKFORD_SPEED;
        update_map_state(map, IS_BOULDER, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        break;
      case LEFT:
        if (count - boulder->collision_time == 60) //1s
        {
          rockford->x -= ROCKFORD_SPEED;
          boulder->x -= ROCKFORD_SPEED;

          if (map[boulder->y / BLOCK_SIZE][boulder->x / BLOCK_SIZE] != IS_EMPTY)
          {
            rockford->x += ROCKFORD_SPEED;
            boulder->x += ROCKFORD_SPEED;
          }

          boulder->collision_time = count;
        }
        rockford->x += ROCKFORD_SPEED;
        update_map_state(map, IS_BOULDER, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        break;
      case RIGHT:
        if (count - boulder->collision_time == 60) //1s
        {
          rockford->x += ROCKFORD_SPEED;
          boulder->x += ROCKFORD_SPEED;

          if (map[boulder->y / BLOCK_SIZE][boulder->x / BLOCK_SIZE] != IS_EMPTY)
          {
            boulder->x -= ROCKFORD_SPEED;
            rockford->x -= ROCKFORD_SPEED;
          }

          boulder->collision_time = count;
        }
        rockford->x -= ROCKFORD_SPEED;
        update_map_state(map, IS_BOULDER, boulder->y / BLOCK_SIZE, boulder->x / BLOCK_SIZE);
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        break;
      default:
        break;
      }
    }
    else
      boulder->collision_time = 0;
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