#include "rockford.h"

void rockford_init(ROCKFORD_STRUCT *rockford)
{
  rockford->x = (BUFFER_WIDTH / 2) - (ROCKFORD_WIDTH / 2);
  rockford->y = (BUFFER_HEIGHT / 2) - (ROCKFORD_HEIGHT / 2);
  rockford->lives = 3;
  rockford->respawn_timer = 0;
  rockford->invincible_timer = 120;
  rockford->source_x = ROCKFORD_SPRITE_WIDTH;
  rockford->source_y = 0;
  rockford->direction = NO_DIRECTION;
  rockford->last_direction = NO_DIRECTION;
  rockford->score = 0;
  rockford->quantity_of_diamonds = 0;
}

void rockford_update(
    ROCKFORD_STRUCT *rockford,
    ALLEGRO_KEYBOARD_STATE *keyState,
    SPRITES_STRUCT *sprites,
    long int count)
{
  if (rockford->lives < 0)
    return;

  if (rockford->respawn_timer)
  {
    rockford->respawn_timer--;
    return;
  }

  if (count % 5 == 0)
  {
    rockford->active = true;

    if (al_key_down(keyState, ALLEGRO_KEY_LEFT))
    {
      rockford->x -= ROCKFORD_SPEED;
      rockford->last_direction = rockford->direction;
      rockford->direction = LEFT;
    }
    else if (al_key_down(keyState, ALLEGRO_KEY_RIGHT))
    {
      rockford->x += ROCKFORD_SPEED;
      rockford->last_direction = rockford->direction;
      rockford->direction = RIGHT;
    }
    else if (al_key_down(keyState, ALLEGRO_KEY_UP))
    {
      rockford->y -= ROCKFORD_SPEED;

      if (rockford->direction != DOWN && rockford->direction != UP)
        rockford->last_direction = rockford->direction;

      rockford->direction = UP;
    }
    else if (al_key_down(keyState, ALLEGRO_KEY_DOWN))
    {
      rockford->y += ROCKFORD_SPEED;

      if (rockford->direction != DOWN && rockford->direction != UP)
        rockford->last_direction = rockford->direction;

      rockford->direction = DOWN;
    }
    else
      rockford->active = false;

    if (rockford->active)
    {
      rockford->source_y = 0;

      if (rockford->direction == LEFT)
        rockford->source_x += al_get_bitmap_width(sprites->rockford_running_left) / 8;
      else if (rockford->direction == RIGHT)
        rockford->source_x += al_get_bitmap_width(sprites->rockford_running_right) / 8;
      else if ((rockford->direction == UP || rockford->direction == DOWN) && rockford->last_direction == LEFT)
        rockford->source_x += al_get_bitmap_width(sprites->rockford_running_left) / 8;
      else if ((rockford->direction == UP || rockford->direction == DOWN) && rockford->last_direction == RIGHT)
        rockford->source_x += al_get_bitmap_width(sprites->rockford_running_left) / 8;
      else
        rockford->source_x = ROCKFORD_SPRITE_WIDTH;

      if (rockford->source_x >= al_get_bitmap_width(sprites->rockford_running_left) && (rockford->direction == LEFT || rockford->direction == UP || rockford->direction == DOWN))
        rockford->source_x = 0;
      else if (rockford->source_x >= al_get_bitmap_width(sprites->rockford_running_right) && (rockford->direction == RIGHT || rockford->direction == UP || rockford->direction == DOWN))
        rockford->source_x = 0;
    }
    else
    {
      rockford->source_x += al_get_bitmap_width(sprites->rockford_waiting) / 8;

      if (rockford->source_x >= al_get_bitmap_width(sprites->rockford_waiting))
      {
        rockford->source_y += al_get_bitmap_height(sprites->rockford_waiting) / 3;

        if (rockford->source_y > 64)
          rockford->source_y = 0;

        rockford->source_x = 0;
      }
    }
  }

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

  if (rockford->active)
  {
    if (rockford->direction == LEFT || (rockford->last_direction == LEFT && (rockford->direction == UP || rockford->direction == DOWN)))
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->rockford_running_left,
          rockford->source_x, rockford->source_y, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT, // source bitmap region
          al_map_rgb(255, 255, 255),                                                             // color, just use white if you don't want a tint
          0, 0,                                                                                  // center of rotation/scaling
          rockford->x, rockford->y,                                                              // destination
          ROCKFORD_SCALE, ROCKFORD_SCALE,                                                        // scale
          0, 0);
    else if (rockford->direction == RIGHT || (rockford->last_direction == RIGHT && (rockford->direction == UP || rockford->direction == DOWN)))
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->rockford_running_right,
          rockford->source_x, rockford->source_y, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT, // source bitmap region
          al_map_rgb(255, 255, 255),                                                             // color, just use white if you don't want a tint
          0, 0,                                                                                  // center of rotation/scaling
          rockford->x, rockford->y,                                                              // destination
          ROCKFORD_SCALE, ROCKFORD_SCALE,                                                        // scale
          0, 0);
    else
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->rockford,
          0, 0, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT, // source bitmap region
          al_map_rgb(255, 255, 255),                           // color, just use white if you don't want a tint
          0, 0,                                                // center of rotation/scaling
          rockford->x, rockford->y,                            // destination
          0.5, 0.5,                                            // scale
          0, 0);
  }
  else
    al_draw_tinted_scaled_rotated_bitmap_region(
        sprites->rockford_waiting,
        rockford->source_x, rockford->source_y, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT, // source bitmap region
        al_map_rgb(255, 255, 255),                                                             // color, just use white if you don't want a tint
        0, 0,                                                                                  // center of rotation/scaling
        rockford->x, rockford->y,                                                              // destination
        ROCKFORD_SCALE, ROCKFORD_SCALE,                                                        // scale
        0, 0);
}