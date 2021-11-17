#include "sprite.h"

ALLEGRO_BITMAP *sprite_grab(SPRITES_STRUCT *sprites, int x, int y, int w, int h)
{
  ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites->_sheet, x, y, w, h);
  initialize(sprite, "sprite grab");
  return sprite;
}

void sprites_init(SPRITES_STRUCT *sprites)
{
  initialize(al_init_image_addon(), "image");

  sprites->_sheet = al_load_bitmap("./resources/sprites.png");
  initialize(sprites->_sheet, "sprites");

  sprites->rockford = sprite_grab(sprites, 0, 0, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT);
  sprites->rockford_running_left = sprite_grab(sprites, 0, 128, ROCKFORD_SPRITE_WIDTH * 8, ROCKFORD_SPRITE_HEIGHT);
  sprites->rockford_running_right = sprite_grab(sprites, 0, 160, ROCKFORD_SPRITE_WIDTH * 8, ROCKFORD_SPRITE_HEIGHT);
  sprites->rockford_waiting = sprite_grab(sprites, 0, 32, ROCKFORD_SPRITE_WIDTH * 8, ROCKFORD_SPRITE_HEIGHT * 3);

  sprites->diamond = sprite_grab(sprites, 0, 320, DIAMOND_SPRITE_WIDTH * 8, DIAMOND_SPRITE_HEIGHT);

  sprites->firefly = sprite_grab(sprites, 0, 288, FIREFLY_SPRITE_WIDTH * 8, FIREFLY_SPRITE_HEIGHT);

  sprites->amoeba = sprite_grab(sprites, 0, 256, AMOEBA_SPRITE_WIDTH * 8, AMOEBA_SPRITE_HEIGHT);

  sprites->butterfly = sprite_grab(sprites, 0, 352, BUTTERFLY_SPRITE_WIDTH * 8, BUTTERFLY_SPRITE_HEIGHT);

  sprites->exit = sprite_grab(sprites, 0, 192, EXIT_SPRITE_WIDTH * 3, EXIT_SPRITE_HEIGHT);

  sprites->magic_wall = sprite_grab(sprites, 96, 192, MAGIC_WALL_SPRITE_WIDTH * 5, MAGIC_WALL_SPRITE_HEIGHT);

  sprites->steel_wall = sprite_grab(sprites, 32, 192, STEEL_WALL_SPRITE_WIDTH, STEEL_WALL_SPRITE_HEIGHT);

  sprites->brick_wall = sprite_grab(sprites, 96, 192, BRICK_WALL_SPRITE_WIDTH, BRICK_WALL_SPRITE_HEIGHT);

  sprites->boulder = sprite_grab(sprites, 0, 224, BOULDER_SPRITE_WIDTH, BOULDER_SPRITE_HEIGHT);

  sprites->dirt = sprite_grab(sprites, 32, 224, DIRT_SPRITE_WIDTH, DIRT_SPRITE_HEIGHT);

  sprites->explosion = sprite_grab(sprites, 0, 0, EXPLOSION_SPRITE_WIDTH * 5, EXPLOSION_SPRITE_HEIGHT);

  sprites->scoreboard = sprite_grab(sprites, 256, 256, SCOREBOARD_SPRITE_WIDTH * 2, SCOREBOARD_SPRITE_HEIGHT * 10);
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

  al_destroy_bitmap(sprites->steel_wall);

  al_destroy_bitmap(sprites->brick_wall);

  al_destroy_bitmap(sprites->boulder);

  al_destroy_bitmap(sprites->dirt);

  al_destroy_bitmap(sprites->explosion);

  al_destroy_bitmap(sprites->scoreboard);

  al_destroy_bitmap(sprites->_sheet);
}