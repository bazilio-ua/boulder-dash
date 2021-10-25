#include "rockford.h"

void rockford_init(ROCKFORD_STRUCT *rockford)
{
  rockford->x = (BUFFER_WIDTH / 2) - (ROCKFORD_WIDTH / 2);
  rockford->y = (BUFFER_HEIGHT / 2) - (ROCKFORD_HEIGHT / 2);
  rockford->lives = 3;
  rockford->respawn_timer = 0;
  rockford->invincible_timer = 120;
}

void rockford_update(ROCKFORD_STRUCT *rockford, unsigned char key[ALLEGRO_KEY_MAX])
{
  if (rockford->lives < 0)
    return;

  if (rockford->respawn_timer)
  {
    rockford->respawn_timer--;
    return;
  }

  if (key[ALLEGRO_KEY_LEFT])
    rockford->x -= ROCKFORD_SPEED;
  if (key[ALLEGRO_KEY_RIGHT])
    rockford->x += ROCKFORD_SPEED;
  if (key[ALLEGRO_KEY_UP])
    rockford->y -= ROCKFORD_SPEED;
  if (key[ALLEGRO_KEY_DOWN])
    rockford->y += ROCKFORD_SPEED;

  if (rockford->x < 0)
    rockford->x = 0;
  if (rockford->y < 0)
    rockford->y = 0;

  if (rockford->x > ROCKFORD_MAX_X)
    rockford->x = ROCKFORD_MAX_X;
  if (rockford->y > ROCKFORD_MAX_Y)
    rockford->y = ROCKFORD_MAX_Y;

  if (rockford->invincible_timer)
    rockford->invincible_timer--;
}

void rockford_draw(ROCKFORD_STRUCT *rockford, SPRITES_STRUCT *sprites)
{
  if (rockford->lives < 0)
    return;
  if (rockford->respawn_timer)
    return;
  if (((rockford->invincible_timer / 2) % 3) == 1)
    return;

  al_draw_bitmap(sprites->rockford, rockford->x, rockford->y, 0);
}