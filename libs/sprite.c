#include "sprite.h"

ALLEGRO_BITMAP *sprite_grab(SPRITES_STRUCT *sprites, int x, int y, int w, int h)
{
  ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites->_sheet, x, y, w, h);
  initialize(sprite, "sprite grab");
  return sprite;
}

void sprites_init(SPRITES_STRUCT *sprites)
{
  sprites->_sheet = al_load_bitmap("./resources/sprites.png");
  initialize(sprites->_sheet, "sprites");

  sprites->rockford = sprite_grab(sprites, 0, 0, ROCKFORD_WIDTH, ROCKFORD_HEIGHT);
  sprites->rockford_running_left = sprite_grab(sprites, 0, 128, ROCKFORD_WIDTH * 8, ROCKFORD_HEIGHT);
  sprites->rockford_running_right = sprite_grab(sprites, 0, 160, ROCKFORD_WIDTH * 8, ROCKFORD_HEIGHT);
  sprites->rockford_waiting = sprite_grab(sprites, 0, 96, ROCKFORD_WIDTH * 8, ROCKFORD_HEIGHT);

  sprites->diamond = sprite_grab(sprites, 0, 320, DIAMOND_WIDTH * 8, DIAMOND_HEIGHT);

  sprites->firefly = sprite_grab(sprites, 0, 288, FIREFLY_WIDTH * 8, FIREFLY_HEIGHT);

  sprites->amoeba = sprite_grab(sprites, 0, 256, AMOEBA_WIDTH * 8, AMOEBA_HEIGHT);
}

void sprites_deinit(SPRITES_STRUCT *sprites)
{
  al_destroy_bitmap(sprites->rockford);
  al_destroy_bitmap(sprites->rockford_running_left);
  al_destroy_bitmap(sprites->rockford_running_right);
  al_destroy_bitmap(sprites->rockford_waiting);

  al_destroy_bitmap(sprites->diamond);

  al_destroy_bitmap(sprites->firefly);

  al_destroy_bitmap(sprites->amoeba);

  al_destroy_bitmap(sprites->_sheet);
}