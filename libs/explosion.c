#include "explosion.h"

/* aloca memória para vetor de explosão */
EXPLOSION_STRUCT *allocate_array_explosion()
{
  return (EXPLOSION_STRUCT *)malloc(sizeof(EXPLOSION_STRUCT) * EXPLOSION_COUNT); /* já possui um tamanho definido porque ele só explode nas redondezas */
}

/* reseta os parâmetros da explosão */
void explosion_reset(EXPLOSION_STRUCT *explosion)
{
  explosion->start = 0;
  explosion->end = 0;
  explosion->x = -BLOCK_SIZE;
  explosion->y = -BLOCK_SIZE;
  explosion->source_x = EXPLOSION_SPRITE_WIDTH;
  explosion->source_y = 0;
  explosion->redraw = false; /* começa como falso, porque só vira true quando algo explode no mapa */
}

/* inicializa o vetor de explosões */
void explosion_init(EXPLOSION_STRUCT *explosion)
{
  for (int i = 0; i < EXPLOSION_COUNT; i++)
    explosion_reset(&explosion[i]);
}

/* atualiza o estado da explosão */
void explosion_update(
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites)
{
  EXPLOSION_STRUCT *explosionPtr;

  for (int i = 0; i < EXPLOSION_COUNT; i++)
  {
    explosionPtr = &explosion[i];

    if (explosionPtr->redraw) /* se a explosão ainda estiver no mapa */
    {
      if (explosionPtr->start % (EXPLOSION_DURATION / UPDATE_SPEED) == 0) /* verificação da atualização da animação da explosão */
        explosionPtr->source_x += al_get_bitmap_width(sprites->explosion) / SUB_EXPLOSION_SPRITE_QTD;
      else if (explosionPtr->start >= explosionPtr->end) /* se a explosão já terminou */
        explosion_reset(explosionPtr);

      explosionPtr->start += 1;
    }
  }
}

/* desenha a explosão */
void explosion_draw(
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < EXPLOSION_COUNT; i++)
    if (explosion[i].redraw) /* se a explosão ainda estiver no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->explosion,
          explosion[i].source_x, explosion[i].source_y, EXPLOSION_SPRITE_WIDTH, EXPLOSION_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                                                                     /* coloração da imagem */
          0, 0,                                                                                          /* centro de rotação */
          explosion[i].x, explosion[i].y,                                                                /* posição atual */
          EXPLOSION_SCALE, EXPLOSION_SCALE,                                                              /* escala */
          0, 0);
}

/* libera memória do vetor de explosões */
void explosion_free(EXPLOSION_STRUCT *explosion)
{
  free(explosion);
}