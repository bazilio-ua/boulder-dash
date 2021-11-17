#include "audio.h"

ALLEGRO_SAMPLE *audio_grep(char *audioPath)
{
  ALLEGRO_SAMPLE *audio = al_load_sample(audioPath);
  initialize(audio, "audio grab");

  return audio;
}

ALLEGRO_SAMPLE_INSTANCE *audio_grep_instance(ALLEGRO_SAMPLE *audio)
{
  ALLEGRO_SAMPLE_INSTANCE *audioInstance = al_create_sample_instance(audio);
  initialize(audioInstance, "audio grab instance");

  return audioInstance;
}

void audio_init(AUDIO_STRUCT *audios)
{
  initialize(al_install_audio(), "audio");
  initialize(al_init_acodec_addon(), "acodec");
  al_reserve_samples(MAX_SAMPLES);

  audios->playing_audio = false;

  audios->background = audio_grep("./resources/background.wav");
  audios->background_instance = audio_grep_instance(audios->background);

  audios->easter_egg = audio_grep("./resources/samba.wav");
  audios->explosion = audio_grep("./resources/explosion.wav");
  audios->steps = audio_grep("./resources/steps.wav");
}

void audio_deinit(AUDIO_STRUCT *audios)
{
  al_destroy_sample(audios->background);
  al_destroy_sample_instance(audios->background_instance);

  al_destroy_sample(audios->easter_egg);
  al_destroy_sample(audios->explosion);
  al_destroy_sample(audios->steps);
}