#include "steel-wall.h"

STEEL_WALL_STRUCT *allocate_array_steel_wall(int steelWallCount)
{
  return (STEEL_WALL_STRUCT *)malloc(sizeof(STEEL_WALL_STRUCT) * steelWallCount);
}

void steel_wall_init(STEEL_WALL_STRUCT *steelWall, int pos_x, int pos_y)
{
  steelWall->x = pos_x;
  steelWall->y = pos_y;
  steelWall->redraw = true;
}

void steel_wall_update(
  STEEL_WALL_STRUCT *steelWall, 
  char map[MAP_HEIGHT][MAP_WIDTH],
  ROCKFORD_STRUCT *rockford, 
  long int count)
{
  if (count % 5 == 0)
    if (isCollision(steelWall->x, steelWall->y, rockford->x, rockford->y))
    {
      switch (rockford->direction)
      {
      case UP:
        rockford->y += ROCKFORD_SPEED;
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        update_map_state(map, IS_STEEL_WALL, steelWall->y / BLOCK_SIZE, steelWall->x / BLOCK_SIZE);
        break;
      case DOWN:
        rockford->y -= ROCKFORD_SPEED;
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        update_map_state(map, IS_STEEL_WALL, steelWall->y / BLOCK_SIZE, steelWall->x / BLOCK_SIZE);
        break;
      case LEFT:
        rockford->x += ROCKFORD_SPEED;
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        update_map_state(map, IS_STEEL_WALL, steelWall->y / BLOCK_SIZE, steelWall->x / BLOCK_SIZE);
        break;
      case RIGHT:
        rockford->x -= ROCKFORD_SPEED;
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        update_map_state(map, IS_STEEL_WALL, steelWall->y / BLOCK_SIZE, steelWall->x / BLOCK_SIZE);
        break;
      default:
        break;
      }
    }
}

void steel_wall_draw(STEEL_WALL_STRUCT *steelWall, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->steel_wall,
      0, 0, STEEL_WALL_SPRITE_WIDTH, STEEL_WALL_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                               // color, just use white if you don't want a tint
      0, 0,                                                    // center of rotation/scaling
      steelWall->x, steelWall->y,                              // destination
      STEEL_WALL_SCALE, STEEL_WALL_SCALE,                      // scale
      0, 0);
}

void steel_wall_free(STEEL_WALL_STRUCT *steelWall)
{
  free(steelWall);
}