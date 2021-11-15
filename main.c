#include "./libs/rockford.h"
#include "./libs/diamond.h"
#include "./libs/firefly.h"
#include "./libs/amoeba.h"
#include "./libs/butterfly.h"
#include "./libs/exit.h"
#include "./libs/magic-wall.h"
#include "./libs/steel-wall.h"
#include "./libs/boulder.h"
#include "./libs/dirt.h"
#include "./libs/brick-wall.h"
#include "./libs/map.h"
#include "./libs/explosion.h"
#include "./libs/utils.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *buffer;

void initialize_display()
{
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  initialize(display, "display");

  buffer = al_create_bitmap(BUFFER_WIDTH, BUFFER_HEIGHT);
  initialize(buffer, "bitmap buffer");
}

void destroy_display()
{
  al_destroy_bitmap(buffer);
  al_destroy_display(display);
}

void pre_draw_display()
{
  al_set_target_bitmap(buffer);
}

void post_draw_display()
{
  al_set_target_backbuffer(display);
  al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_WIDTH, BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);

  al_flip_display();
}

int main()
{
  srand(time(NULL));

  int i;
  long frames;
  long score;
  char map[MAP_HEIGHT][MAP_WIDTH];
  bool restart = true;

  SPRITES_STRUCT sprites;
  EXIT_STRUCT exit;

  FIREFLY_STRUCT *firefly;
  int fireflyCount = 0;

  STEEL_WALL_STRUCT *steelWall;
  int steelWallCount = 0;

  ROCKFORD_STRUCT *rockford;

  BRICK_WALL_STRUCT *brickWall;
  int brickWallCount = 0;

  BOULDER_STRUCT *boulder;
  int boulderCount = 0;

  BUTTERFLY_STRUCT *butterfly;
  int butterflyCount = 0;

  DIRT_STRUCT *dirt;
  int dirtCount = 0;

  DIAMOND_STRUCT *diamond;
  int diamondCount = 0;

  AMOEBA_STRUCT *amoeba;
  int amoebaCount = 0;

  MAGIC_WALL_STRUCT *magicWall;
  int magicWallCount = 0;

  EXPLOSION_STRUCT *explosion;

  initialize_map(map, "./resources/map.txt");
  count_map_objects(map,
                    &steelWallCount,
                    &brickWallCount,
                    &boulderCount,
                    &dirtCount,
                    &diamondCount,
                    &fireflyCount,
                    &butterflyCount,
                    &amoebaCount,
                    &magicWallCount);

  steelWall = allocate_array_steel_wall(steelWallCount);
  initialize(steelWall, "steel wall");

  brickWall = allocate_array_brick_wall(brickWallCount);
  initialize(brickWall, "brick wall");

  dirt = allocate_array_dirt(dirtCount);
  initialize(dirt, "dirt");

  firefly = allocate_array_firefly(fireflyCount);
  initialize(firefly, "firefly");

  butterfly = allocate_array_butterfly(butterflyCount);
  initialize(butterfly, "butterfly");

  magicWall = allocate_array_magic_wall(magicWallCount);
  initialize(magicWall, "magic wall");

  rockford = allocate_rockford();
  initialize(rockford, "rockford");

  diamond = allocate_array_diamond(MAX_OBJECT_QUANTITY);
  initialize(diamond, "diamond");

  boulder = allocate_array_boulder(MAX_OBJECT_QUANTITY);
  initialize(boulder, "boulder");

  amoeba = allocate_array_amoeba(MAX_OBJECT_QUANTITY);
  initialize(amoeba, "amoeba");

  explosion = allocate_array_explosion(EXPLOSION_COUNT);
  initialize(explosion, "explosion");
  explosion_init(explosion);

  initialize(al_init(), "allegro");
  initialize(al_install_keyboard(), "keyboard");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  initialize(timer, "timer");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  initialize(queue, "queue");

  initialize_display();

  initialize(al_init_image_addon(), "image");
  sprites_init(&sprites);

  initialize(al_init_primitives_addon(), "primitives");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  frames = 0;
  score = 0;

  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;
  ALLEGRO_KEYBOARD_STATE keyState;

  al_start_timer(timer);

  while (!rockford->won && !rockford->lose && !done)
  {
    if (restart)
    {
      initialize_map(map, "./resources/map.txt");

      steelWallCount = 0;
      brickWallCount = 0;
      boulderCount = 0;
      dirtCount = 0;
      diamondCount = 0;
      fireflyCount = 0;
      butterflyCount = 0;
      amoebaCount = 0;
      magicWallCount = 0;

      init_map_objects(
          map,
          steelWall,
          brickWall,
          boulder,
          dirt,
          diamond,
          rockford,
          firefly,
          butterfly,
          amoeba,
          magicWall,
          &steelWallCount,
          &brickWallCount,
          &boulderCount,
          &dirtCount,
          &diamondCount,
          &fireflyCount,
          &butterflyCount,
          &amoebaCount,
          &magicWallCount,
          event.timer.count);

      restart = false;
    }

    al_wait_for_event(queue, &event);
    al_get_keyboard_state(&keyState);

    switch (event.type)
    {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    case ALLEGRO_EVENT_TIMER:

      if (rockford->redraw)
      {
        rockford_update(
            rockford,
            map,
            explosion,
            &keyState,
            &sprites,
            event.timer.count);

        if (!rockford->redraw)
          restart = true;
      }

      firefly_update(
          firefly,
          &fireflyCount,
          map,
          explosion,
          &sprites,
          event.timer.count);

      butterfly_update(
          butterfly,
          diamond,
          &butterflyCount,
          &diamondCount,
          map,
          explosion,
          &sprites,
          event.timer.count);

      boulder_update(
          boulder,
          &boulderCount,
          map,
          rockford,
          event.timer.count);

      diamond_update(
          diamond,
          &diamondCount,
          map,
          &sprites,
          rockford,
          event.timer.count);

      amoeba_update(
          amoeba,
          boulder,
          diamond,
          &amoebaCount,
          &boulderCount,
          &diamondCount,
          map,
          explosion,
          &sprites,
          event.timer.count);

      steel_wall_update(
          steelWall,
          &steelWallCount,
          map,
          rockford,
          event.timer.count);

      dirt_update(
          dirt,
          &dirtCount,
          map,
          rockford,
          event.timer.count);

      brick_wall_update(
          brickWall,
          &brickWallCount,
          map,
          rockford,
          event.timer.count);

      magic_wall_update(
          magicWall,
          diamond,
          &magicWallCount,
          &diamondCount,
          map,
          &sprites,
          event.timer.count);

      explosion_update(
          explosion,
          &sprites,
          event.timer.count);

      redraw = true;
      break;
    default:
      break;
    }

    if (redraw && al_is_event_queue_empty(queue))
    {
      pre_draw_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));

      if (rockford->redraw)
        rockford_draw(rockford, &sprites);

      for (i = 0; i < steelWallCount; i++)
        if (steelWall[i].redraw)
          steel_wall_draw(&steelWall[i], &sprites);

      for (i = 0; i < brickWallCount; i++)
        if (brickWall[i].redraw)
          brick_wall_draw(&brickWall[i], &sprites);

      for (i = 0; i < magicWallCount; i++)
        if (magicWall[i].redraw)
          magic_wall_draw(&magicWall[i], &sprites);

      for (i = 0; i < boulderCount; i++)
        if (boulder[i].redraw)
          boulder_draw(&boulder[i], &sprites);

      for (i = 0; i < dirtCount; i++)
        if (dirt[i].redraw)
          dirt_draw(&dirt[i], &sprites);

      for (i = 0; i < diamondCount; i++)
        if (diamond[i].redraw)
          diamond_draw(&diamond[i], &sprites);

      for (i = 0; i < fireflyCount; i++)
        if (firefly[i].redraw)
          firefly_draw(&firefly[i], &sprites);

      for (i = 0; i < butterflyCount; i++)
        if (butterfly[i].redraw)
          butterfly_draw(&butterfly[i], &sprites);

      for (i = 0; i < amoebaCount; i++)
        if (amoeba[i].redraw)
          amoeba_draw(&amoeba[i], &sprites);

      for (i = 0; i < EXPLOSION_COUNT; i++)
        if (explosion[i].redraw)
          explosion_draw(&explosion[i], &sprites);

      post_draw_display();
      redraw = false;
    }
  }

  for (int i = 0; i < MAP_HEIGHT; i++)
  {
    for (int j = 0; j < MAP_WIDTH; j++)
    {
      printf("%c ", map[i][j]);
    }
    printf("\n");
  }

  steel_wall_free(steelWall);
  brick_wall_free(brickWall);
  boulder_free(boulder);
  dirt_free(dirt);
  diamond_free(diamond);
  rockford_free(rockford);
  firefly_free(firefly);
  butterfly_free(butterfly);
  explosion_free(explosion);
  amoeba_free(amoeba);
  magic_wall_free(magicWall);
  sprites_deinit(&sprites);
  destroy_display();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}