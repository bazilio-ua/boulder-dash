#ifndef _DISPLAYH_
#define _DISPLAYH_

#include "utils.h"

void initialize_display(
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer);

void destroy_display(
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer); 

void pre_draw_display(ALLEGRO_BITMAP **buffer); 

void post_draw_display(
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer);

#endif