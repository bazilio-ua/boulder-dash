#include "diamond.h"

DIAMOND_STRUCT *allocate_array_diamond(int diamondCount)
{
  return (DIAMOND_STRUCT *)malloc(sizeof(DIAMOND_STRUCT) * diamondCount);
}

void diamond_init(DIAMOND_STRUCT *diamond, int pos_x, int pos_y)
{
  diamond->x = pos_x;
  diamond->y = pos_y;
  diamond->source_x = DIAMOND_SPRITE_WIDTH;
  diamond->source_y = 0;
  diamond->redraw = true;
  diamond->falling = false;
}

void diamond_update(
    DIAMOND_STRUCT *diamond,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    ROCKFORD_STRUCT *rockford,
    long int count)
{

  if (!isSpaceDiamond(map, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE))
  {
    diamond->redraw = false;
    return;
  }

  if (count % 5 == 0)
  {

    if (diamond->falling &&
        (isSpaceRockford(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE) ||
         isSpaceFirefly(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE) ||
         isSpaceButterfly(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE)))
    {
      update_map_state(map, IS_EMPTY, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE);
      diamond->y += BLOCK_SIZE;
      update_map_state(map, IS_DIAMOND, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE);
      return;
    }

    diamond->falling = false;

    if (isSpaceEmpty(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE))
    {
      update_map_state(map, IS_EMPTY, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE);
      diamond->y += BLOCK_SIZE;
      diamond->falling = true;
      update_map_state(map, IS_DIAMOND, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE);
    }
    else if (
        isSpaceEmpty(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE - 1) &&
        isSpaceEmpty(map, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE - 1) &&
        (isSpaceBoulder(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE) ||
         isSpaceBrickWall(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE) ||
         isSpaceDiamond(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE)))
    {
      update_map_state(map, IS_EMPTY, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE);
      diamond->x -= BLOCK_SIZE;
      update_map_state(map, IS_DIAMOND, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE);
    }
    else if (
        isSpaceEmpty(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE + 1) &&
        isSpaceEmpty(map, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE + 1) &&
        (isSpaceBoulder(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE) ||
         isSpaceBrickWall(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE) ||
         isSpaceDiamond(map, diamond->y / BLOCK_SIZE + 1, diamond->x / BLOCK_SIZE)))
    {
      update_map_state(map, IS_EMPTY, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE);
      diamond->x += BLOCK_SIZE;
      update_map_state(map, IS_DIAMOND, diamond->y / BLOCK_SIZE, diamond->x / BLOCK_SIZE);
    }

    diamond->source_x += al_get_bitmap_width(sprites->diamond) / 8;

    if (diamond->source_x >= al_get_bitmap_width(sprites->diamond))
      diamond->source_x = 0;
  }

  if (isCollision(diamond->x, diamond->y, rockford->x, rockford->y))
  {
    rockford->quantity_of_diamonds++;
    rockford->score += DIAMOND_SCORE;
    diamond->redraw = false;
  }
}

void diamond_draw(DIAMOND_STRUCT *diamond, SPRITES_STRUCT *sprites)
{
  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->diamond,
      diamond->source_x, diamond->source_y, DIAMOND_SPRITE_WIDTH, DIAMOND_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                         // color, just use white if you don't want a tint
      0, 0,                                                                              // center of rotation/scaling
      diamond->x, diamond->y,                                                            // destination
      DIAMOND_SCALE, DIAMOND_SCALE,                                                      // scale
      0, 0);
  // al_draw_bitmap_region(sprites->diamond, diamond->source_x, diamond->source_y, DIAMOND_SPRITE_WIDTH, DIAM, diamond->x, diamond->y, 0);
}

void diamond_free(DIAMOND_STRUCT *diamond)
{
  free(diamond);
}