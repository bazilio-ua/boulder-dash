#include "./libs/rockford.h"
#include "./libs/diamond.h"
#include "./libs/firefly.h"
#include "./libs/amoeba.h"

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
  SPRITES_STRUCT sprites;
  ROCKFORD_STRUCT rockford;
  DIAMOND_STRUCT diamond;
  FIREFLY_STRUCT firefly;
  AMOEBA_STRUCT amoeba;
  long frames;
  long score;

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

  rockford_init(&rockford);
  diamond_init(&diamond, 0, 0);
  firefly_init(&firefly, 50, 50);
  amoeba_init(&amoeba, 100, 100);

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
      rockford_update(&rockford, &keyState, &sprites);
      diamond_update(&diamond, &sprites);
      firefly_update(&firefly, &sprites);
      amoeba_update(&amoeba, &sprites);
      redraw = true;
      break;
    default:
      break;
    }

    if (redraw && al_is_event_queue_empty(queue))
    {
      pre_draw_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));
      rockford_draw(&rockford, &sprites);
      diamond_draw(&diamond, &sprites);
      firefly_draw(&firefly, &sprites);
      amoeba_draw(&amoeba, &sprites);
      post_draw_display();
      redraw = false;
    }
  }

  sprites_deinit(&sprites);
  destroy_display();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}