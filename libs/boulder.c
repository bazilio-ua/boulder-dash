#include "boulder.h"

void boulder_init(BOULDER_STRUCT *boulder, int pos_x, int pos_y)
{
  boulder->x = pos_x;
  boulder->y = pos_y;
}

void boulder_update(BOULDER_STRUCT *boulder, SPRITES_STRUCT *sprites, long int count)
{
  return;
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