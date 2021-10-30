#include "magic-wall.h"

void magic_wall_init(MAGIC_WALL_STRUCT *magicWall, int pos_x, int pos_y)
{
  magicWall->x = pos_x;
  magicWall->y = pos_y;
  magicWall->source_x = MAGIC_WALL_SPRITE_WIDTH;
  magicWall->source_y = 0;
}

void magic_wall_update(MAGIC_WALL_STRUCT *magicWall, SPRITES_STRUCT *sprites, long int count)
{
  if (count % 5 == 0)
  {
    magicWall->source_x += al_get_bitmap_width(sprites->magic_wall) / 5;

    if (magicWall->source_x >= al_get_bitmap_width(sprites->magic_wall))
      magicWall->source_x = 0;
  }
}

void magic_wall_draw(MAGIC_WALL_STRUCT *magicWall, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->magic_wall,
      magicWall->source_x, magicWall->source_y, MAGIC_WALL_SPRITE_WIDTH, MAGIC_WALL_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                   // color, just use white if you don't want a tint
      0, 0,                                                                                        // center of rotation/scaling
      magicWall->x, magicWall->y,                                                                        // destination
      MAGIC_WALL_SCALE, MAGIC_WALL_SCALE,                                                                  // scale
      0, 0);
}