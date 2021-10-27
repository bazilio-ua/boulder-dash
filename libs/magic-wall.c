#include "magic-wall.h"

void magic_wall_init(MAGIC_WALL_STRUCT *magicWall, int pos_x, int pos_y)
{
  magicWall->x = pos_x;
  magicWall->y = pos_y;
  magicWall->source_x = MAGIC_WALL_WIDTH;
  magicWall->source_y = 0;
}

void magic_wall_update(MAGIC_WALL_STRUCT *magicWall, SPRITES_STRUCT *sprites)
{
  magicWall->source_x += al_get_bitmap_width(sprites->magic_wall) / 5;

  if (magicWall->source_x >= al_get_bitmap_width(sprites->magic_wall))
    magicWall->source_x = 0;
}

void magic_wall_draw(MAGIC_WALL_STRUCT *magicWall, SPRITES_STRUCT *sprites)
{
  al_draw_bitmap_region(sprites->magic_wall, magicWall->source_x, magicWall->source_y, MAGIC_WALL_WIDTH, MAGIC_WALL_HEIGHT, magicWall->x, magicWall->y, 0);
}