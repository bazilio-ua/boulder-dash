#include "explosion.h"

EXPLOSION_STRUCT *allocate_array_explosion()
{
  return (EXPLOSION_STRUCT *)malloc(sizeof(EXPLOSION_STRUCT) * EXPLOSION_COUNT);
}

void explosion_reset(EXPLOSION_STRUCT *explosion)
{
  explosion->start = 0;
  explosion->end = 0;
  explosion->x = 0;
  explosion->y = 0;
  explosion->source_x = EXPLOSION_SPRITE_WIDTH;
  explosion->source_y = 0;
  explosion->redraw = false;
}

void explosion_init(EXPLOSION_STRUCT *explosion)
{
  for (int i = 0; i < EXPLOSION_COUNT; i++)
    explosion_reset(&explosion[i]);
}

void explosion_update(
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    long int count)
{
  EXPLOSION_STRUCT *explosionPtr;

  for (int i = 0; i < EXPLOSION_COUNT; i++)
  {
    explosionPtr = &explosion[i];

    if (explosionPtr->start % (EXPLOSION_DURATION / 5) == 0)
      explosionPtr->source_x += al_get_bitmap_width(sprites->explosion) / 5;
    else if (explosionPtr->start >= explosionPtr->end)
      explosion_reset(explosionPtr);

    explosionPtr->start += 1;
  }
}

void explosion_draw(EXPLOSION_STRUCT *explosion, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->explosion,
      explosion->source_x, explosion->source_y, EXPLOSION_SPRITE_WIDTH, EXPLOSION_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                 // color, just use white if you don't want a tint
      0, 0,                                                                                      // center of rotation/scaling
      explosion->x, explosion->y,                                                                // destination
      EXPLOSION_SCALE, EXPLOSION_SCALE,                                                          // scale
      0, 0);
}

void explosion_free(EXPLOSION_STRUCT *explosion)
{
  free(explosion);
}