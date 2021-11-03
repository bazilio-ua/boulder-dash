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
  int i, j;
  SPRITES_STRUCT sprites;
  FIREFLY_STRUCT firefly;
  AMOEBA_STRUCT amoeba;
  BUTTERFLY_STRUCT butterfly;
  EXIT_STRUCT exit;
  MAGIC_WALL_STRUCT magicWall;

  STEEL_WALL_STRUCT *steelWall;
  int steelWallCount = 0;

  ROCKFORD_STRUCT *rockford;

  BRICK_WALL_STRUCT *brickWall;
  int brickWallCount = 0;

  BOULDER_STRUCT *boulder;
  int boulderCount = 0;

  DIRT_STRUCT *dirt;
  int dirtCount = 0;

  DIAMOND_STRUCT *diamond;
  int diamondCount = 0;

  char map[MAP_HEIGHT][MAP_WIDTH];
  long frames;
  long score;

  initialize_map(map, "./resources/map.txt");
  count_map_objects(map, &steelWallCount, &brickWallCount, &boulderCount, &dirtCount, &diamondCount);

  steelWall = allocate_array_steel_wall(steelWallCount);
  initialize(steelWall, "steel wall");
  steelWallCount = 0;

  brickWall = allocate_array_brick_wall(brickWallCount);
  initialize(brickWall, "brick wall");
  brickWallCount = 0;

  boulder = allocate_array_boulder(boulderCount);
  initialize(boulder, "boulder");
  boulderCount = 0;

  dirt = allocate_array_dirt(dirtCount);
  initialize(dirt, "dirt");
  dirtCount = 0;

  diamond = allocate_array_diamond(diamondCount);
  initialize(diamond, "diamond");
  diamondCount = 0;

  rockford = allocate_rockford();
  initialize(rockford, "rockford");

  init_map_objects(
      map,
      steelWall,
      brickWall,
      boulder,
      dirt,
      diamond,
      rockford,
      &steelWallCount,
      &brickWallCount,
      &boulderCount,
      &dirtCount,
      &diamondCount);

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

  // rockford_init(&rockford);
  // diamond_init(&diamond, 0, 0);
  firefly_init(&firefly, 96, 0);
  amoeba_init(&amoeba, 16, 0);
  butterfly_init(&butterfly, 48, 0);
  exit_init(&exit, 80, 0);
  magic_wall_init(&magicWall, 112, 0);
  // steel_wall_init(&steelWall, 128, 0);
  // boulder_init(&boulder, 32, 0);
  // dirt_init(&dirt, 64, 0);

  frames = 0;
  score = 0;

  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;
  ALLEGRO_KEYBOARD_STATE keyState;

  al_start_timer(timer);

  while (!done)
  {
    al_wait_for_event(queue, &event);
    al_get_keyboard_state(&keyState);

    switch (event.type)
    {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    case ALLEGRO_EVENT_TIMER:
      rockford_update(rockford, map, &keyState, &sprites, event.timer.count);

      for (i = 0; i < diamondCount; i++)
        diamond_update(&diamond[i], &sprites, rockford, event.timer.count);

      for (i = 0; i < dirtCount; i++)
        dirt_update(&dirt[i], rockford, event.timer.count);

      for (i = 0; i < brickWallCount; i++)
        brick_wall_update(&brickWall[i], map, rockford, event.timer.count);

      for (i = 0; i < steelWallCount; i++)
        steel_wall_update(&steelWall[i], map, rockford, event.timer.count);

      for (i = 0; i < boulderCount; i++)
        boulder_update(&boulder[i], map, rockford, event.timer.count);

      // firefly_update(&firefly, &sprites, event.timer.count);
      // amoeba_update(&amoeba, &sprites, event.timer.count);
      // butterfly_update(&butterfly, &sprites, event.timer.count);
      // exit_update(&exit, &sprites, event.timer.count);
      // magic_wall_update(&magicWall, &sprites, event.timer.count);
      // boulder_update(&boulder, &sprites, event.timer.count);
      // dirt_update(&dirt, &sprites, event.timer.count);
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
      // if (diamond.redraw)
      //   diamond_draw(&diamond, &sprites);
      // firefly_draw(&firefly, &sprites);
      // amoeba_draw(&amoeba, &sprites);
      // butterfly_draw(&butterfly, &sprites);
      // exit_draw(&exit, &sprites);
      // magic_wall_draw(&magicWall, &sprites);
      // steel_wall_draw(&steelWall, &sprites);
      // boulder_draw(&boulder, &sprites);
      // dirt_draw(&dirt, &sprites);
      for (i = 0; i < steelWallCount; i++)
      {
        if (steelWall[i].redraw)
          steel_wall_draw(&steelWall[i], &sprites);
      }

      for (i = 0; i < brickWallCount; i++)
      {
        if (brickWall[i].redraw)
          brick_wall_draw(&brickWall[i], &sprites);
      }

      for (i = 0; i < boulderCount; i++)
      {
        if (boulder[i].redraw)
          boulder_draw(&boulder[i], &sprites);
      }

      for (i = 0; i < dirtCount; i++)
      {
        if (dirt[i].redraw)
          dirt_draw(&dirt[i], &sprites);
      }

      for (i = 0; i < diamondCount; i++)
      {
        if (diamond[i].redraw)
          diamond_draw(&diamond[i], &sprites);
      }

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
  sprites_deinit(&sprites);
  destroy_display();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}