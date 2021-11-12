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

void butterfly_update(
    BUTTERFLY_STRUCT *butterfly,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    long int count)
{
  if (isSpaceEmpty(map, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE))
  {
    butterfly->redraw = false;
    return;
  }

  else if (!isSpaceButterfly(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE)))
  {
    int butterflyLine = butterfly->y / BLOCK_SIZE;
    int butterflyColumn = butterfly->x / BLOCK_SIZE;

    EXPLOSION_STRUCT *explosionPtr;
    int explosionCount = 0;

    for (int i = butterflyLine - 1; i <= butterflyLine + 1; i++)
      for (int j = butterflyColumn - 1; j <= butterflyColumn + 1; j++)
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

    butterfly->redraw = false;
  }

  else if (count % 5 == 0)
  {
    if (verify_rockford_amoeba_presence_in_neighborhood_butterfly(butterfly, map))
      butterfly->redraw = false;
    else
      switch (butterfly->direction)
      {
      case RIGHT:
        if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE + 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_down(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE + 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_right(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE - 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_up(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE - 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_left(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        break;
      case UP:
        if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE + 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_right(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE - 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_up(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE - 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_left(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE + 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_down(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        break;
      case LEFT:
        if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE - 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_up(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE - 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_left(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE + 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_down(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE + 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_right(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        break;
      case DOWN:
        if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE - 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_left(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE + 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_down(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE + 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_right(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE - 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_up(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        break;
      default:
        if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE + 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_right(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE + 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_down(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE - 1), (butterfly->x / BLOCK_SIZE)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_up(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        else if (isSpaceEmpty(map, (butterfly->y / BLOCK_SIZE), (butterfly->x / BLOCK_SIZE - 1)))
        {
          update_map_state(map, IS_EMPTY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
          move_butterfly_left(butterfly);
          update_map_state(map, IS_BUTTERFLY, butterfly->y / BLOCK_SIZE, butterfly->x / BLOCK_SIZE);
        }

        break;
      }

    butterfly->source_x += al_get_bitmap_width(sprites->butterfly) / 8;

    if (butterfly->source_x >= al_get_bitmap_width(sprites->butterfly))
      butterfly->source_x = 0;
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