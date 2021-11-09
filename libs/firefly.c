#include "firefly.h"

FIREFLY_STRUCT *allocate_array_firefly(int fireflyCount)
{
  return (FIREFLY_STRUCT *)malloc(sizeof(FIREFLY_STRUCT) * fireflyCount);
}

void firefly_init(FIREFLY_STRUCT *firefly, int pos_x, int pos_y)
{
  firefly->x = pos_x;
  firefly->y = pos_y;
  firefly->source_x = FIREFLY_SPRITE_WIDTH;
  firefly->source_y = 0;
  firefly->redraw = true;
  firefly->direction = NO_DIRECTION;
}

//move the firefly to the up
void move_firefly_up(FIREFLY_STRUCT *firefly)
{
  firefly->y -= BLOCK_SIZE;
  firefly->direction = UP;
}

//move the firefly to the down
void move_firefly_down(FIREFLY_STRUCT *firefly)
{
  firefly->y += BLOCK_SIZE;
  firefly->direction = DOWN;
}

//move the firefly to the left
void move_firefly_left(FIREFLY_STRUCT *firefly)
{
  firefly->x -= BLOCK_SIZE;
  firefly->direction = LEFT;
}

//move the firefly to the right
void move_firefly_right(FIREFLY_STRUCT *firefly)
{
  firefly->x += BLOCK_SIZE;
  firefly->direction = RIGHT;
}

bool verify_rockford_presence_in_neighborhood_firefly(FIREFLY_STRUCT *firefly, char map[MAP_HEIGHT][MAP_WIDTH])
{
  if (isSpaceRockford(map, firefly->y / BLOCK_SIZE + 1, firefly->x / BLOCK_SIZE))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->y += BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (isSpaceRockford(map, firefly->y / BLOCK_SIZE - 1, firefly->x / BLOCK_SIZE))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->y -= BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (isSpaceRockford(map, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE + 1))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->x += BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (isSpaceRockford(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE) - 1))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->x -= BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  return false;
}

void firefly_update(FIREFLY_STRUCT *firefly, char map[MAP_HEIGHT][MAP_WIDTH], SPRITES_STRUCT *sprites, long int count)
{
  if (!isSpaceFirefly(map, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE))
  {
    firefly->redraw = false;
    return;
  }

  if (count % 5 == 0)
  {
    if (verify_rockford_presence_in_neighborhood_firefly(firefly, map))
      firefly->redraw = false;

    switch (firefly->direction)
    {
    case RIGHT:
      if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE - 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_up(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE + 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_right(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE + 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_down(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE - 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_left(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      break;
    case UP:
      if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE - 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_left(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE - 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_up(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE + 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_right(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE + 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_down(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      break;
    case LEFT:
      if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE + 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_down(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE - 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_left(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE - 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_up(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE + 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_right(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      break;
    case DOWN:
      if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE + 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_right(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE + 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_down(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE - 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_left(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE - 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_up(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      break;
    default:
      if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE - 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_up(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }

      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE - 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_left(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }

      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE + 1), (firefly->x / BLOCK_SIZE)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_down(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }

      else if (isSpaceEmpty(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE + 1)))
      {
        update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
        move_firefly_right(firefly);
        update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
      }
      break;
    }

    firefly->source_x += al_get_bitmap_width(sprites->firefly) / 8;

    if (firefly->source_x >= al_get_bitmap_width(sprites->firefly))
      firefly->source_x = 0;
  }
}

void firefly_draw(FIREFLY_STRUCT *firefly, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->firefly,
      firefly->source_x, firefly->source_y, FIREFLY_SPRITE_WIDTH, FIREFLY_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                         // color, just use white if you don't want a tint
      0, 0,                                                                              // center of rotation/scaling
      firefly->x, firefly->y,                                                            // destination
      FIREFLY_SCALE, FIREFLY_SCALE,                                                      // scale
      0, 0);
}

void firefly_free(FIREFLY_STRUCT *firefly)
{
  free(firefly);
}