#include "game.h"

void game_initialization(
    ALLEGRO_TIMER **timer,
    ALLEGRO_EVENT_QUEUE **queue,
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    AUDIO_STRUCT *audio,
    ROCKFORD_STRUCT **rockford,
    EXIT_STRUCT **exit,
    FIREFLY_STRUCT **firefly,
    int *fireflyCount,
    STEEL_WALL_STRUCT **steelWall,
    int *steelWallCount,
    BRICK_WALL_STRUCT **brickWall,
    int *brickWallCount,
    BOULDER_STRUCT **boulder,
    int *boulderCount,
    BUTTERFLY_STRUCT **butterfly,
    int *butterflyCount,
    DIRT_STRUCT **dirt,
    int *dirtCount,
    DIAMOND_STRUCT **diamond,
    int *diamondCount,
    AMOEBA_STRUCT **amoeba,
    int *amoebaCount,
    MAGIC_WALL_STRUCT **magicWall,
    int *magicWallCount,
    EXPLOSION_STRUCT **explosion)
{

  initialize_map(map, "./resources/map.txt");
  count_map_objects(map,
                    steelWallCount,
                    brickWallCount,
                    boulderCount,
                    dirtCount,
                    diamondCount,
                    fireflyCount,
                    butterflyCount,
                    amoebaCount,
                    magicWallCount);

  *steelWall = allocate_array_steel_wall(*steelWallCount);
  initialize(*steelWall, "steel wall");

  *brickWall = allocate_array_brick_wall(*brickWallCount);
  initialize(*brickWall, "brick wall");

  *dirt = allocate_array_dirt(*dirtCount);
  initialize(*dirt, "dirt");

  *firefly = allocate_array_firefly(*fireflyCount);
  initialize(*firefly, "firefly");

  *butterfly = allocate_array_butterfly(*butterflyCount);
  initialize(*butterfly, "butterfly");

  *magicWall = allocate_array_magic_wall(*magicWallCount);
  initialize(*magicWall, "magic wall");

  *rockford = allocate_rockford();
  initialize(*rockford, "rockford");

  *exit = allocate_exit();
  initialize(*exit, "exit");
  exit_init(*exit, -BLOCK_SIZE, -BLOCK_SIZE);

  *diamond = allocate_array_diamond(MAX_OBJECT_QUANTITY);
  initialize(*diamond, "diamond");

  *boulder = allocate_array_boulder(MAX_OBJECT_QUANTITY);
  initialize(*boulder, "boulder");

  *amoeba = allocate_array_amoeba(MAX_OBJECT_QUANTITY);
  initialize(*amoeba, "amoeba");

  *explosion = allocate_array_explosion(EXPLOSION_COUNT);
  initialize(*explosion, "explosion");
  explosion_init(*explosion);

  initialize(al_init(), "allegro");
  initialize(al_install_keyboard(), "keyboard");
  audio_init(audio);

  al_set_sample_instance_playmode(audio->background_instance, ALLEGRO_PLAYMODE_LOOP);
  al_attach_sample_instance_to_mixer(audio->background_instance, al_get_default_mixer());

  *timer = al_create_timer(1.0 / 60.0);
  initialize(*timer, "timer");

  *queue = al_create_event_queue();
  initialize(*queue, "queue");

  initialize_display(display, buffer);

  sprites_init(sprites);

  initialize(al_init_primitives_addon(), "primitives");

  al_register_event_source(*queue, al_get_keyboard_event_source());
  al_register_event_source(*queue, al_get_display_event_source(*display));
  al_register_event_source(*queue, al_get_timer_event_source(*timer));

  al_play_sample_instance(audio->background_instance);

  al_start_timer(*timer);
}

void game_restart(
    bool *restart,
    int count,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT **rockford,
    EXIT_STRUCT **exit,
    FIREFLY_STRUCT **firefly,
    int *fireflyCount,
    STEEL_WALL_STRUCT **steelWall,
    int *steelWallCount,
    BRICK_WALL_STRUCT **brickWall,
    int *brickWallCount,
    BOULDER_STRUCT **boulder,
    int *boulderCount,
    BUTTERFLY_STRUCT **butterfly,
    int *butterflyCount,
    DIRT_STRUCT **dirt,
    int *dirtCount,
    DIAMOND_STRUCT **diamond,
    int *diamondCount,
    AMOEBA_STRUCT **amoeba,
    int *amoebaCount,
    MAGIC_WALL_STRUCT **magicWall,
    int *magicWallCount,
    EXPLOSION_STRUCT **explosion)
{
  initialize_map(map, "./resources/map.txt");

  *steelWallCount = 0;
  *brickWallCount = 0;
  *boulderCount = 0;
  *dirtCount = 0;
  *diamondCount = 0;
  *fireflyCount = 0;
  *butterflyCount = 0;
  *amoebaCount = 0;
  *magicWallCount = 0;

  init_map_objects(
      map,
      *steelWall,
      *brickWall,
      *boulder,
      *dirt,
      *diamond,
      *rockford,
      *firefly,
      *butterfly,
      *amoeba,
      *magicWall,
      steelWallCount,
      brickWallCount,
      boulderCount,
      dirtCount,
      diamondCount,
      fireflyCount,
      butterflyCount,
      amoebaCount,
      magicWallCount,
      count);

  exit_init(*exit, -BLOCK_SIZE, -BLOCK_SIZE);

  *restart = false;
}

void game_update(
    ALLEGRO_KEYBOARD_STATE *keyState,
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    SPRITES_STRUCT *sprites,
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *butterflyCount,
    int *diamondCount,
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    ROCKFORD_STRUCT *rockford,
    AMOEBA_STRUCT *amoeba,
    int *amoebaCount,
    DIRT_STRUCT *dirt,
    int *dirtCount,
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount,
    EXIT_STRUCT *exit,
    long int count,
    bool *restart)
{
  if (rockford->redraw)
  {
    rockford_update(
        rockford,
        map,
        explosion,
        audio,
        keyState,
        sprites,
        count);

    if (!rockford->redraw)
      *restart = true;
  }

  firefly_update(
      firefly,
      fireflyCount,
      map,
      explosion,
      audio,
      sprites,
      count);

  butterfly_update(
      butterfly,
      diamond,
      butterflyCount,
      diamondCount,
      map,
      explosion,
      audio,
      sprites,
      count);

  boulder_update(
      boulder,
      boulderCount,
      map,
      rockford,
      count);

  diamond_update(
      diamond,
      diamondCount,
      map,
      sprites,
      rockford,
      count);

  amoeba_update(
      amoeba,
      boulder,
      diamond,
      amoebaCount,
      boulderCount,
      diamondCount,
      map,
      explosion,
      audio,
      sprites,
      count);

  dirt_update(
      dirt,
      dirtCount,
      map,
      rockford,
      count);

  brick_wall_update(
      brickWall,
      brickWallCount,
      map,
      rockford,
      count);

  magic_wall_update(
      magicWall,
      diamond,
      magicWallCount,
      diamondCount,
      map,
      sprites,
      count);

  explosion_update(
      explosion,
      sprites,
      count);

  exit_update(
      exit,
      rockford,
      map,
      sprites,
      count);
}

void game_draw(
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer,
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *butterflyCount,
    int *diamondCount,
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    ROCKFORD_STRUCT *rockford,
    AMOEBA_STRUCT *amoeba,
    int *amoebaCount,
    DIRT_STRUCT *dirt,
    int *dirtCount,
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount,
    STEEL_WALL_STRUCT *steelWall,
    int *steelWallCount,
    EXIT_STRUCT *exit)
{
  pre_draw_display(buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));

  rockford_draw(rockford, sprites);

  steel_wall_draw(steelWall, steelWallCount, sprites);

  brick_wall_draw(brickWall, brickWallCount, sprites);

  magic_wall_draw(magicWall, magicWallCount, sprites);

  boulder_draw(boulder, boulderCount, sprites);

  dirt_draw(dirt, dirtCount, sprites);

  diamond_draw(diamond, diamondCount, sprites);

  firefly_draw(firefly, fireflyCount, sprites);

  butterfly_draw(butterfly, butterflyCount, sprites);

  amoeba_draw(amoeba, amoebaCount, sprites);

  explosion_draw(explosion, sprites);

  exit_draw(exit, sprites);

  draw_scoreboard(rockford, sprites);

  post_draw_display(display, buffer);
}

void game_clear(
    ALLEGRO_TIMER **timer,
    ALLEGRO_EVENT_QUEUE **queue,
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer,
    FIREFLY_STRUCT **firefly,
    EXPLOSION_STRUCT **explosion,
    SPRITES_STRUCT *sprites,
    AUDIO_STRUCT *audio,
    BUTTERFLY_STRUCT **butterfly,
    DIAMOND_STRUCT **diamond,
    BOULDER_STRUCT **boulder,
    ROCKFORD_STRUCT **rockford,
    AMOEBA_STRUCT **amoeba,
    DIRT_STRUCT **dirt,
    BRICK_WALL_STRUCT **brickWall,
    MAGIC_WALL_STRUCT **magicWall,
    STEEL_WALL_STRUCT **steelWall,
    EXIT_STRUCT **exit)
{
  steel_wall_free(*steelWall);
  brick_wall_free(*brickWall);
  boulder_free(*boulder);
  dirt_free(*dirt);
  diamond_free(*diamond);
  rockford_free(*rockford);
  firefly_free(*firefly);
  butterfly_free(*butterfly);
  explosion_free(*explosion);
  amoeba_free(*amoeba);
  magic_wall_free(*magicWall);
  exit_free(*exit);
  sprites_deinit(sprites);
  audio_deinit(audio);

  destroy_display(display, buffer);
  al_destroy_timer(*timer);
  al_destroy_event_queue(*queue);
}
