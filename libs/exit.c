#include "exit.h"

EXIT_STRUCT *allocate_exit()
{
  return malloc(sizeof(EXIT_STRUCT));
}

void exit_init(EXIT_STRUCT *exit, int pos_x, int pos_y)
{
  exit->x = pos_x;
  exit->y = pos_y;
  exit->source_x = EXIT_SPRITE_WIDTH;
  exit->source_y = 0;
  exit->redraw = false;
}

void exit_update(
    EXIT_STRUCT *exit,
    ROCKFORD_STRUCT *rockford,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    long int count)
{
  if (isSpaceRockford(map, exit->y / BLOCK_SIZE, exit->x / BLOCK_SIZE))
  {
    exit->redraw = false;
    rockford->won = true;
    return;
  }

  if (
      rockford->quantity_of_diamonds >= EXIT_AMOUNT_NEEDED_TO_APPEAR &&
      !exit->redraw)
  {
    int randomLine = -1;
    int randomColumn = -1;

    while (randomLine == -1 && randomColumn == -1)
    {
      randomLine = generateRandomNumberBetween(0, MAP_HEIGHT - 1);
      randomColumn = generateRandomNumberBetween(0, MAP_WIDTH - 1);

      if (isSpaceDirt(map, randomLine, randomColumn) || isSpaceEmpty(map, randomLine, randomColumn))
        break;

      randomLine = -1;
      randomColumn = -1;
    }

    update_map_state(map, IS_EXIT, randomLine, randomColumn);

    exit->x = randomColumn * BLOCK_SIZE;
    exit->y = randomLine * BLOCK_SIZE;
    exit->source_x = EXIT_SPRITE_WIDTH;
    exit->source_y = 0;
    exit->redraw = true;
  }

  if (exit->redraw)
  {
    if (count % 5 == 0)
    {
      exit->source_x += al_get_bitmap_width(sprites->exit) / 3;

      if (exit->source_x >= al_get_bitmap_width(sprites->exit))
        exit->source_x = 0;
    }
  }
}

void exit_draw(EXIT_STRUCT *exit, SPRITES_STRUCT *sprites)
{
  if (exit->redraw)
    al_draw_tinted_scaled_rotated_bitmap_region(
        sprites->exit,
        exit->source_x, exit->source_y, EXIT_SPRITE_WIDTH, EXIT_SPRITE_HEIGHT, // source bitmap region
        al_map_rgb(255, 255, 255),                                             // color, just use white if you don't want a tint
        0, 0,                                                                  // center of rotation/scaling
        exit->x, exit->y,                                                      // destination
        EXIT_SCALE, EXIT_SCALE,                                                // scale
        0, 0);
}

void exit_free(EXIT_STRUCT *exit)
{
  free(exit);
}