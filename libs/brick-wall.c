#include "brick-wall.h"

BRICK_WALL_STRUCT *allocate_array_brick_wall(int brickWallCount)
{
  return (BRICK_WALL_STRUCT *)malloc(sizeof(BRICK_WALL_STRUCT) * brickWallCount);
}

void brick_wall_init(BRICK_WALL_STRUCT *brickWall, int pos_x, int pos_y)
{
  brickWall->x = pos_x;
  brickWall->y = pos_y;
  brickWall->redraw = true;
}

void brick_wall_update(
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT *rockford,
    long int count)
{
  BRICK_WALL_STRUCT *brickWallPtr;

  for (int i = 0; i < *brickWallCount; i++)
  {
    brickWallPtr = &brickWall[i];

    if (!isSpaceBrickWall(map, brickWallPtr->y / BLOCK_SIZE, brickWallPtr->x / BLOCK_SIZE))
      brickWallPtr->redraw = false;
  }
}

void brick_wall_draw(BRICK_WALL_STRUCT *brickWall, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->brick_wall,
      0, 0, BRICK_WALL_SPRITE_WIDTH, BRICK_WALL_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                               // color, just use white if you don't want a tint
      0, 0,                                                    // center of rotation/scaling
      brickWall->x, brickWall->y,                              // destination
      BRICK_WALL_SCALE, BRICK_WALL_SCALE,                      // scale
      0, 0);
}

void brick_wall_free(BRICK_WALL_STRUCT *brickWall)
{
  free(brickWall);
}