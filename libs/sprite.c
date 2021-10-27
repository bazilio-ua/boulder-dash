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

  sprites->butterfly = sprite_grab(sprites, 0, 352, BUTTERFLY_WIDTH * 8, BUTTERFLY_HEIGHT);

  sprites->exit = sprite_grab(sprites, 0, 192, EXIT_WIDTH * 3, EXIT_HEIGHT);

  sprites->magic_wall = sprite_grab(sprites, 96, 192, MAGIC_WALL_WIDTH * 5, MAGIC_WALL_HEIGHT);
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

  al_destroy_bitmap(sprites->butterfly);

  al_destroy_bitmap(sprites->exit);

  al_destroy_bitmap(sprites->magic_wall);

  al_destroy_bitmap(sprites->_sheet);
}