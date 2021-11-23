#include "display.h"

void initialize_display(
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer)
{
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  initialize(*display, "display");

  *buffer = al_create_bitmap(BUFFER_WIDTH, BUFFER_HEIGHT);
  initialize(*buffer, "bitmap buffer");
}

void destroy_display(
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer)
{
  al_destroy_bitmap(*buffer);
  al_destroy_display(*display);
}

void pre_draw_display(ALLEGRO_BITMAP **buffer)
{
  al_set_target_bitmap(*buffer);
}

void post_draw_display(
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer)
{
  al_set_target_backbuffer(*display);
  al_draw_scaled_bitmap(*buffer, 0, 0, BUFFER_WIDTH, BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);

  al_flip_display();
}
