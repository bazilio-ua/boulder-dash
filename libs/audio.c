#include "audio.h"

/* pega o áudio e verifica se é nulo ou não */
ALLEGRO_SAMPLE *audio_grep(char *audioPath)
{
  ALLEGRO_SAMPLE *audio = al_load_sample(audioPath);
  initialize(audio, "audio grab");

  return audio;
}

/* cria uma instância de áudio e verifica se é nulo ou não */
ALLEGRO_SAMPLE_INSTANCE *audio_grep_instance(ALLEGRO_SAMPLE *audio)
{
  ALLEGRO_SAMPLE_INSTANCE *audioInstance = al_create_sample_instance(audio);
  initialize(audioInstance, "audio grab instance");

  return audioInstance;
}

/* inicializa os áudios */
void audio_init(AUDIO_STRUCT *audios)
{
  initialize(al_install_audio(), "audio");
  initialize(al_init_acodec_addon(), "acodec");
  al_reserve_samples(MAX_SAMPLES);

  audios->playing_audio = false;

  audios->background = audio_grep("./res/background.wav");
  audios->background_instance = audio_grep_instance(audios->background);

  audios->easter_egg = audio_grep("./res/samba.wav");
  audios->explosion = audio_grep("./res/explosion.wav");
  audios->steps = audio_grep("./res/steps.wav");
}

/* libera os áudios */
void audio_deinit(AUDIO_STRUCT *audios)
{
  al_destroy_sample(audios->background);
  al_destroy_sample_instance(audios->background_instance);

  al_destroy_sample(audios->easter_egg);
  al_destroy_sample(audios->explosion);
  al_destroy_sample(audios->steps);
}