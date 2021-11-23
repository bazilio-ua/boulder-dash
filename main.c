#include "./libs/game.h"
#include "./libs/display.h"

int main()
{
  srand(time(NULL));
  char map[MAP_HEIGHT][MAP_WIDTH];
  bool restart = true;
  bool done = false;

  ALLEGRO_TIMER *timer;
  ALLEGRO_EVENT_QUEUE *queue;
  ALLEGRO_DISPLAY *display;
  ALLEGRO_BITMAP *buffer;
  ALLEGRO_EVENT event;
  ALLEGRO_KEYBOARD_STATE keyState;
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

  while (!rockford->won && !rockford->lose && !done)
  {
    if (restart)
      game_restart(
          &restart,
          event.timer.count,
          map,
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

    al_wait_for_event(queue, &event);
    al_get_keyboard_state(&keyState);

    switch (event.type)
    {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    case ALLEGRO_EVENT_TIMER:
      game_update(
          &keyState,
          firefly,
          &fireflyCount,
          map,
          explosion,
          &audio,
          &sprites,
          butterfly,
          diamond,
          &butterflyCount,
          &diamondCount,
          boulder,
          &boulderCount,
          rockford,
          amoeba,
          &amoebaCount,
          dirt,
          &dirtCount,
          brickWall,
          &brickWallCount,
          magicWall,
          &magicWallCount,
          exit,
          event.timer.count,
          &restart);

      if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
        done = true;

      break;
    default:
      break;
    }

    if (al_is_event_queue_empty(queue))
      game_draw(
          &display,
          &buffer,
          firefly,
          &fireflyCount,
          explosion,
          &sprites,
          butterfly,
          diamond,
          &butterflyCount,
          &diamondCount,
          boulder,
          &boulderCount,
          rockford,
          amoeba,
          &amoebaCount,
          dirt,
          &dirtCount,
          brickWall,
          &brickWallCount,
          magicWall,
          &magicWallCount,
          steelWall,
          &steelWallCount,
          exit);
  }

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