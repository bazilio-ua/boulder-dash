#include "butterfly.h"

BUTTERFLY_STRUCT *allocate_array_butterfly(int butterflyCount)
{
  return (BUTTERFLY_STRUCT *)malloc(sizeof(BUTTERFLY_STRUCT) * butterflyCount);
}

void butterfly_init(BUTTERFLY_STRUCT *butterfly, int pos_x, int pos_y)
{
  butterfly->x = pos_x;
  butterfly->y = pos_y;
  butterfly->source_x = BUTTERFLY_SPRITE_WIDTH;
  butterfly->source_y = 0;
  butterfly->direction = NO_DIRECTION;
  butterfly->redraw = true;
  butterfly->amount_of_diamonds = generateRandomNumberBetween(0, 5);
}

//move the butterfly to the up
void move_butterfly_up(BUTTERFLY_STRUCT *butterfly)
{
  butterfly->y -= BLOCK_SIZE;
  butterfly->direction = UP;
}

//move the butterfly to the down
void move_butterfly_down(BUTTERFLY_STRUCT *butterfly)
{
  butterfly->y += BLOCK_SIZE;
  butterfly->direction = DOWN;
}

//move the butterfly to the left
void move_butterfly_left(BUTTERFLY_STRUCT *butterfly)
{
  butterfly->x -= BLOCK_SIZE;
  butterfly->direction = LEFT;
}

//move the butterfly to the right
void move_butterfly_right(BUTTERFLY_STRUCT *butterfly)
{
  butterfly->x += BLOCK_SIZE;
  butterfly->direction = RIGHT;
}

bool verify_rockford_amoeba_presence_in_neighborhood_butterfly(BUTTERFLY_STRUCT *firefly, char map[MAP_HEIGHT][MAP_WIDTH])
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

void generate_diamonds(
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH])
{
  DIAMOND_STRUCT *diamondTemp;
  int i = 0;

  while (i < butterfly->amount_of_diamonds)
  {
    diamondTemp = &diamond[*diamondCount];

    int randomLine = generateRandomNumberBetween(0, MAP_HEIGHT - 1);
    int randomColumn = generateRandomNumberBetween(0, MAP_WIDTH - 1);

    if (isSpaceDirt(map, randomLine, randomColumn))
    {
      (*diamondCount)++;
      update_map_state(map, IS_DIAMOND, randomLine, randomColumn);

      diamondTemp->x = randomColumn * BLOCK_SIZE;
      diamondTemp->y = randomLine * BLOCK_SIZE;
      diamondTemp->source_x = DIAMOND_SPRITE_WIDTH;
      diamondTemp->source_y = 0;
      diamondTemp->redraw = true;
      diamondTemp->falling = false;

      i++;
    }
  }

  butterfly->redraw = false;
}

void butterfly_update(
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *butterflyCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    long int count)
{
  BUTTERFLY_STRUCT *butterflyPtr;

  for (int i = 0; i < *butterflyCount; i++)
  {
    butterflyPtr = &butterfly[i];

    if (butterflyPtr->redraw)
    {
      if (isSpaceEmpty(map, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE))
      {
        generate_diamonds(butterflyPtr, diamond, diamondCount, map);
        return;
      }

      if (!isSpaceButterfly(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE)))
      {
        int butterflyPtrLine = butterflyPtr->y / BLOCK_SIZE;
        int butterflyPtrColumn = butterflyPtr->x / BLOCK_SIZE;

        EXPLOSION_STRUCT *explosionPtr;
        int explosionCount = 0;

        for (int i = butterflyPtrLine - 1; i <= butterflyPtrLine + 1; i++)
          for (int j = butterflyPtrColumn - 1; j <= butterflyPtrColumn + 1; j++)
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

        generate_diamonds(butterflyPtr, diamond, diamondCount, map);

        return;
      }

      if (count % 5 == 0)
      {
        if (verify_rockford_amoeba_presence_in_neighborhood_butterfly(butterflyPtr, map))
          generate_diamonds(butterflyPtr, diamond, diamondCount, map);
        else
          switch (butterflyPtr->direction)
          {
          case RIGHT:
            if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_down(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_right(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_up(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_left(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            break;
          case UP:
            if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_right(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_up(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_left(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_down(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            break;
          case LEFT:
            if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_up(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_left(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_down(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_right(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            break;
          case DOWN:
            if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_left(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_down(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_right(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_up(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            break;
          default:
            if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_right(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_down(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_up(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            else if (isSpaceEmpty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
            {
              update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
              move_butterfly_left(butterflyPtr);
              update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
            }

            break;
          }

        butterflyPtr->source_x += al_get_bitmap_width(sprites->butterfly) / 8;

        if (butterflyPtr->source_x >= al_get_bitmap_width(sprites->butterfly))
          butterflyPtr->source_x = 0;
      }
    }
  }
}

void butterfly_draw(BUTTERFLY_STRUCT *butterfly, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->butterfly,
      butterfly->source_x, butterfly->source_y, BUTTERFLY_SPRITE_WIDTH, BUTTERFLY_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                 // color, just use white if you don't want a tint
      0, 0,                                                                                      // center of rotation/scaling
      butterfly->x, butterfly->y,                                                                // destination
      BUTTERFLY_SCALE, BUTTERFLY_SCALE,                                                          // scale
      0, 0);
}

void butterfly_free(BUTTERFLY_STRUCT *butterfly)
{
  free(butterfly);
}