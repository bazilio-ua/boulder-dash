#include "rockford.h"

ROCKFORD_STRUCT *allocate_rockford()
{
  return malloc(sizeof(ROCKFORD_STRUCT));
}

void rockford_init(ROCKFORD_STRUCT *rockford, int pos_x, int pos_y)
{
  if (!rockford->lives)
    rockford->lives = 3;

  rockford->x = pos_x;
  rockford->y = pos_y;
  rockford->respawn_timer = 0;
  rockford->invincible_timer = 120;
  rockford->source_x = ROCKFORD_SPRITE_WIDTH;
  rockford->source_y = 0;
  rockford->direction = NO_DIRECTION;
  rockford->last_direction = NO_DIRECTION;
  rockford->score = 0;
  rockford->quantity_of_diamonds = 0;
  rockford->won = false;
  rockford->lose = false;
  rockford->redraw = true;

  if (!rockford->is_easter_egg_active)
  {
    rockford->is_easter_egg_active = false;
    rockford->started_time_easter_egg = 0;
  }
}

void rockford_update(
    ROCKFORD_STRUCT *rockford,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    unsigned char key[ALLEGRO_KEY_MAX],
    SPRITES_STRUCT *sprites,
    long int count)
{
  if (rockford->respawn_timer)
  {
    rockford->respawn_timer--;
    return;
  }

  if (isSpaceEmpty(map, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE))
  {
    rockford->redraw = false;
    rockford->lives = rockford->lives - 1;

    return;
  }

  if (!isSpaceRockford(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE)))
  {
    int rockfordLine = rockford->y / BLOCK_SIZE;
    int rockfordColumn = rockford->x / BLOCK_SIZE;

    EXPLOSION_STRUCT *explosionPtr;
    int explosionCount = 0;

    for (int i = rockfordLine - 1; i <= rockfordLine + 1; i++)
      for (int j = rockfordColumn - 1; j <= rockfordColumn + 1; j++)
        if (!isSpaceSteelWall(map, i, j))
        {
          update_map_state(map, IS_EMPTY, i, j);

          explosionPtr = &explosion[explosionCount];

          explosionPtr->x = j * BLOCK_SIZE;
          explosionPtr->y = i * BLOCK_SIZE;
          explosionPtr->redraw = true;
          explosionPtr->start = 0;
          explosionPtr->end = EXPLOSION_DURATION;

          explosionCount++;
        }

    rockford->lives = rockford->lives - 1;
    rockford->redraw = false;
    al_play_sample(audio->explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    if (rockford->lives == 0)
      rockford->lose = true;
  }

  if (count % 5 == 0)
  {

    rockford->active = true;

    if (key[ALLEGRO_KEY_LEFT])
    {
      if (isSpaceEmpty(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE) - 1) ||
          isSpaceDirt(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE) - 1) ||
          isSpaceDiamond(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE) - 1) ||
          isSpaceExit(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE) - 1))
      {
        update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        rockford->x -= ROCKFORD_SPEED;
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
      }

      rockford->last_direction = rockford->direction;
      rockford->direction = LEFT;
    }
    else if (key[ALLEGRO_KEY_RIGHT])
    {
      if (isSpaceEmpty(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE) + 1) ||
          isSpaceDirt(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE) + 1) ||
          isSpaceDiamond(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE) + 1) ||
          isSpaceExit(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE) + 1))
      {
        update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        rockford->x += ROCKFORD_SPEED;
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
      }

      rockford->last_direction = rockford->direction;
      rockford->direction = RIGHT;
    }
    else if (key[ALLEGRO_KEY_UP])
    {
      if (isSpaceEmpty(map, (rockford->y / BLOCK_SIZE) - 1, (rockford->x / BLOCK_SIZE)) ||
          isSpaceDirt(map, (rockford->y / BLOCK_SIZE) - 1, (rockford->x / BLOCK_SIZE)) ||
          isSpaceDiamond(map, (rockford->y / BLOCK_SIZE) - 1, (rockford->x / BLOCK_SIZE)) ||
          isSpaceExit(map, (rockford->y / BLOCK_SIZE) - 1, (rockford->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        rockford->y -= ROCKFORD_SPEED;
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
      }

      if (rockford->direction != DOWN && rockford->direction != UP)
        rockford->last_direction = rockford->direction;

      rockford->direction = UP;
    }
    else if (key[ALLEGRO_KEY_DOWN])
    {
      if (isSpaceEmpty(map, (rockford->y / BLOCK_SIZE) + 1, (rockford->x / BLOCK_SIZE)) ||
          isSpaceDirt(map, (rockford->y / BLOCK_SIZE) + 1, (rockford->x / BLOCK_SIZE)) ||
          isSpaceDiamond(map, (rockford->y / BLOCK_SIZE) + 1, (rockford->x / BLOCK_SIZE)) ||
          isSpaceExit(map, (rockford->y / BLOCK_SIZE) + 1, (rockford->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        rockford->y += ROCKFORD_SPEED;
        update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
      }

      if (rockford->direction != DOWN && rockford->direction != UP)
        rockford->last_direction = rockford->direction;

      rockford->direction = DOWN;
    }
    else
      rockford->active = false;

    if (rockford->active)
    {
      al_play_sample(audio->steps, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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

  if (rockford->invincible_timer)
    rockford->invincible_timer--;
}

void rockford_draw(ROCKFORD_STRUCT *rockford, SPRITES_STRUCT *sprites)
{
  if (rockford->redraw)
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
            ROCKFORD_SCALE, ROCKFORD_SCALE,                      // scale
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
}

void rockford_free(ROCKFORD_STRUCT *rockford)
{
  free(rockford);
}