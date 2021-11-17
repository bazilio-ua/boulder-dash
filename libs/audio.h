#ifndef _AUDIOH_
#define _AUDIOH_

#include "utils.h"

typedef struct AUDIO_STRUCT
{
  ALLEGRO_SAMPLE *background;
  ALLEGRO_SAMPLE_INSTANCE *background_instance;

  ALLEGRO_SAMPLE *easter_egg;

  ALLEGRO_SAMPLE *explosion;

  ALLEGRO_SAMPLE *steps;
  
  bool playing_audio;
} AUDIO_STRUCT;

void audio_init(AUDIO_STRUCT *audios);

void audio_deinit(AUDIO_STRUCT *audios);

#endif