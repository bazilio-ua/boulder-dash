#include "dirt.h"

/* Aloca memória para o vetor de terras */
DIRT_STRUCT *allocate_array_dirt(int dirtCount)
{
  return (DIRT_STRUCT *)malloc(sizeof(DIRT_STRUCT) * dirtCount);
}

/* iniciliza uma terra */
void dirt_init(
    DIRT_STRUCT *dirt,
    int pos_x,
    int pos_y)
{
  dirt->x = pos_x;
  dirt->y = pos_y;
  dirt->redraw = true;
}

/* atualiza o estado da terra */
void dirt_update(
    DIRT_STRUCT *dirt,
    int *dirtCount,
    char map[MAP_HEIGHT][MAP_WIDTH])
{
  DIRT_STRUCT *dirtPtr;

  for (int i = 0; i < *dirtCount; i++) /* loop sobre o vetor de terras */
  {
    dirtPtr = &dirt[i];

    if (dirtPtr->redraw)                                                         /* verifica se a terra ainda esta no mapa */
      if (!is_space_dirt(map, dirtPtr->y / BLOCK_SIZE, dirtPtr->x / BLOCK_SIZE)) /* verifica se a terra esta em um lugar que esta sendo ocupado por qualquer outra coisa, pois isso significa que houve uma explosão em sua redondeza ou o herói passou por cima */
        dirtPtr->redraw = false;                                                 /* se o de cima for verdade, então para de desenhar a terra */
  }
}

/* desenha a terra */
void dirt_draw(
    DIRT_STRUCT *dirt,
    int *dirtCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *dirtCount; i++)
    if (dirt[i].redraw) /* verifica se a terra ainda esta no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->dirt,
          0, 0, AMOEBA_SPRITE_WIDTH, AMOEBA_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                       /* coloração da imagem */
          0, 0,                                            /* centro de rotação */
          dirt[i].x, dirt[i].y,                            /* posição atual */
          DIRT_SCALE, DIRT_SCALE,                          /* escala */
          0, 0);
}

/* libera memória do vetor de terras */
void dirt_free(DIRT_STRUCT *dirt)
{
  free(dirt);
}