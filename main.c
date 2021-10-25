#include "./libs/utils.h"
#include "./libs/rockford.h"

typedef struct SPRITES
{
  ALLEGRO_BITMAP *_sheet;
  ALLEGRO_BITMAP *rockford;
} SPRITES;

SPRITES sprites;
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *buffer;
ROCKFORD_STRUCT rockford;
unsigned char key[ALLEGRO_KEY_MAX];
long frames;
long score;

ALLEGRO_BITMAP *sprite_grab(int x, int y, int w, int h)
{
  ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
  initialize(sprite, "sprite grab");
  return sprite;
}

void sprites_init()
{
  sprites._sheet = al_load_bitmap("./resources/sprites.png");
  initialize(sprites._sheet, "sprites");

  sprites.rockford = sprite_grab(4, 2, ROCKFORD_WIDTH, ROCKFORD_HEIGHT);
}

void sprites_deinit()
{
  al_destroy_bitmap(sprites.rockford);
  al_destroy_bitmap(sprites._sheet);
}

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

void keyboard_init()
{
  memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT *event)
{
  switch (event->type)
  {
  case ALLEGRO_EVENT_TIMER:
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
      key[i] &= KEY_SEEN;
    break;

  case ALLEGRO_EVENT_KEY_DOWN:
    key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
    break;
  case ALLEGRO_EVENT_KEY_UP:
    key[event->keyboard.keycode] &= KEY_RELEASED;
    break;
  }
}

// void rockford_init()
// {
//   rockford.x = (BUFFER_WIDTH / 2) - (ROCKFORD_WIDTH / 2);
//   rockford.y = (BUFFER_HEIGHT / 2) - (ROCKFORD_HEIGHT / 2);
//   rockford.lives = 3;
//   rockford.respawn_timer = 0;
//   rockford.invincible_timer = 120;
// }

// void rockford_update()
// {
//   if (rockford.lives < 0)
//     return;

//   if (rockford.respawn_timer)
//   {
//     rockford.respawn_timer--;
//     return;
//   }

//   if (key[ALLEGRO_KEY_LEFT])
//     rockford.x -= ROCKFORD_SPEED;
//   if (key[ALLEGRO_KEY_RIGHT])
//     rockford.x += ROCKFORD_SPEED;
//   if (key[ALLEGRO_KEY_UP])
//     rockford.y -= ROCKFORD_SPEED;
//   if (key[ALLEGRO_KEY_DOWN])
//     rockford.y += ROCKFORD_SPEED;

//   if (rockford.x < 0)
//     rockford.x = 0;
//   if (rockford.y < 0)
//     rockford.y = 0;

//   if (rockford.x > ROCKFORD_MAX_X)
//     rockford.x = ROCKFORD_MAX_X;
//   if (rockford.y > ROCKFORD_MAX_Y)
//     rockford.y = ROCKFORD_MAX_Y;

//   if (rockford.invincible_timer)
//     rockford.invincible_timer--;
// }

// void rockford_draw()
// {
//   if (rockford.lives < 0)
//     return;
//   if (rockford.respawn_timer)
//     return;
//   if (((rockford.invincible_timer / 2) % 3) == 1)
//     return;

//   al_draw_bitmap(sprites.rockford, rockford.x, rockford.y, 0);
// }

int main()
{
  initialize(al_init(), "allegro");
  initialize(al_install_keyboard(), "keyboard");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  initialize(timer, "timer");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  initialize(queue, "queue");

  initialize_display();

  initialize(al_init_image_addon(), "image");
  sprites_init();

  initialize(al_init_primitives_addon(), "primitives");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  keyboard_init();
  rockford_init(&rockford);

  frames = 0;
  score = 0;

  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;

  al_start_timer(timer);

  while (1)
  {
    al_wait_for_event(queue, &event);

    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER:
      rockford_update(&rockford, key);

      if (key[ALLEGRO_KEY_ESCAPE])
        done = true;

      redraw = true;
      frames++;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    }

    if (done)
      break;

    keyboard_update(&event);

    if (redraw && al_is_event_queue_empty(queue))
    {
      pre_draw_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));
      rockford_draw(&rockford, &sprites);
      post_draw_display();
      redraw = false;
    }
  }

  sprites_deinit();
  destroy_display();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}