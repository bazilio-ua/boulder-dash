#include "./libs/game.h"

int main()
{
  srand(time(NULL));
  char map[MAP_HEIGHT][MAP_WIDTH];
  bool restart = true;
  bool done = false;

  unsigned char keyboard[ALLEGRO_KEY_MAX];
  ALLEGRO_TIMER *timer;
  ALLEGRO_EVENT_QUEUE *queue;
  ALLEGRO_DISPLAY *display;
  ALLEGRO_BITMAP *buffer;
  ALLEGRO_EVENT event;
  SPRITES_STRUCT sprites;
  AUDIO_STRUCT audio;

  ROCKFORD_STRUCT *rockford = NULL;
  EXIT_STRUCT *exit = NULL;
  FIREFLY_STRUCT *firefly = NULL;
  int fireflyCount = 0;
  STEEL_WALL_STRUCT *steelWall = NULL;
  int steelWallCount = 0;
  BRICK_WALL_STRUCT *brickWall = NULL;
  int brickWallCount = 0;
  BOULDER_STRUCT *boulder = NULL;
  int boulderCount = 0;
  BUTTERFLY_STRUCT *butterfly = NULL;
  int butterflyCount = 0;
  DIRT_STRUCT *dirt = NULL;
  int dirtCount = 0;
  DIAMOND_STRUCT *diamond = NULL;
  int diamondCount = 0;
  AMOEBA_STRUCT *amoeba = NULL;
  int amoebaCount = 0;
  MAGIC_WALL_STRUCT *magicWall = NULL;
  int magicWallCount = 0;
  EXPLOSION_STRUCT *explosion = NULL;

  game_initialization(
      keyboard,
      &timer,
      &queue,
      &display,
      &buffer,
      map,
      &sprites,
      &audio,
      &rockford,
      &exit,
      &firefly,
      &fireflyCount,
      &steelWall,
      &steelWallCount,
      &brickWall,
      &brickWallCount,
      &boulder,
      &boulderCount,
      &butterfly,
      &butterflyCount,
      &dirt,
      &dirtCount,
      &diamond,
      &diamondCount,
      &amoeba,
      &amoebaCount,
      &magicWall,
      &magicWallCount,
      &explosion);

  handle_game(
      keyboard,
      &event,
      &queue,
      &display,
      &buffer,
      map,
      &sprites,
      &audio,
      &rockford,
      &exit,
      &firefly,
      &fireflyCount,
      &steelWall,
      &steelWallCount,
      &brickWall,
      &brickWallCount,
      &boulder,
      &boulderCount,
      &butterfly,
      &butterflyCount,
      &dirt,
      &dirtCount,
      &diamond,
      &diamondCount,
      &amoeba,
      &amoebaCount,
      &magicWall,
      &magicWallCount,
      &explosion,
      &restart,
      &done);

  game_clear(
      &timer,
      &queue,
      &display,
      &buffer,
      &firefly,
      &explosion,
      &sprites,
      &audio,
      &butterfly,
      &diamond,
      &boulder,
      &rockford,
      &amoeba,
      &dirt,
      &brickWall,
      &magicWall,
      &steelWall,
      &exit);

  return 0;
}