#include "steel-wall.h"

void steel_wall_init(STEEL_WALL_STRUCT *steelWall, int pos_x, int pos_y)
{
  steelWall->x = pos_x;
  steelWall->y = pos_y;
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