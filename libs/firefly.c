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

bool verify_rockford_amoeba_presence_in_neighborhood_firefly(FIREFLY_STRUCT *firefly, char map[MAP_HEIGHT][MAP_WIDTH])
{
  if (isSpaceRockford(map, firefly->y / BLOCK_SIZE + 1, firefly->x / BLOCK_SIZE) ||
      isSpaceAmoeba(map, firefly->y / BLOCK_SIZE + 1, firefly->x / BLOCK_SIZE))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->y += BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (isSpaceRockford(map, firefly->y / BLOCK_SIZE - 1, firefly->x / BLOCK_SIZE) ||
      isSpaceAmoeba(map, firefly->y / BLOCK_SIZE - 1, firefly->x / BLOCK_SIZE))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->y -= BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (isSpaceRockford(map, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE + 1) ||
      isSpaceAmoeba(map, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE + 1))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->x += BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (isSpaceRockford(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE) - 1) ||
      isSpaceAmoeba(map, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE - 1))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->x -= BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  return false;
}

void firefly_update(
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    SPRITES_STRUCT *sprites,
    long int count)
{
  FIREFLY_STRUCT *fireflyPtr;

  for (int i = 0; i < *fireflyCount; i++)
  {
    fireflyPtr = &firefly[i];

    if (fireflyPtr->redraw)
    {
      if (isSpaceEmpty(map, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE))
      {
        fireflyPtr->redraw = false;
        return;
      }

      else if (!isSpaceFirefly(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE)))
      {
        int fireflyPtrLine = fireflyPtr->y / BLOCK_SIZE;
        int fireflyPtrColumn = fireflyPtr->x / BLOCK_SIZE;

        EXPLOSION_STRUCT *explosionPtr;
        int explosionCount = 0;

        for (int i = fireflyPtrLine - 1; i <= fireflyPtrLine + 1; i++)
          for (int j = fireflyPtrColumn - 1; j <= fireflyPtrColumn + 1; j++)
            if (!isSpaceSteelWall(map, i, j) && !isSpaceExit(map, i, j))
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

        al_play_sample(audio->explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        fireflyPtr->redraw = false;
      }

      else if (count % 5 == 0)
      {
        if (verify_rockford_amoeba_presence_in_neighborhood_firefly(fireflyPtr, map))
          fireflyPtr->redraw = false;
        else
          switch (fireflyPtr->direction)
          {
          case RIGHT:
            if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_up(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_right(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_down(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_left(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            break;
          case UP:
            if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_left(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_up(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_right(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_down(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            break;
          case LEFT:
            if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_down(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_left(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_up(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_right(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            break;
          case DOWN:
            if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_right(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_down(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_left(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_up(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            break;
          default:
            if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_up(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_left(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_down(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
              move_firefly_right(fireflyPtr);
              update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
            }
            break;
          }

        fireflyPtr->source_x += al_get_bitmap_width(sprites->firefly) / 8;

        if (fireflyPtr->source_x >= al_get_bitmap_width(sprites->firefly))
          fireflyPtr->source_x = 0;
      }
    }
  }
}

void firefly_draw(
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *fireflyCount; i++)
    if (firefly[i].redraw)
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->firefly,
          firefly[i].source_x, firefly[i].source_y, FIREFLY_SPRITE_WIDTH, FIREFLY_SPRITE_HEIGHT, // source bitmap region
          al_map_rgb(255, 255, 255),                                                             // color, just use white if you don't want a tint
          0, 0,                                                                                  // center of rotation/scaling
          firefly[i].x, firefly[i].y,                                                            // destination
          FIREFLY_SCALE, FIREFLY_SCALE,                                                          // scale
          0, 0);
}

void firefly_free(FIREFLY_STRUCT *firefly)
{
  free(firefly);
}