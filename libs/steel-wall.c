#include "steel-wall.h"

/* aloca memória para o vetor de paredes de aço */
STEEL_WALL_STRUCT *allocate_array_steel_wall(int steelWallCount)
{
  return (STEEL_WALL_STRUCT *)malloc(sizeof(STEEL_WALL_STRUCT) * steelWallCount);
}

/* inicializa a parede de aço */
void steel_wall_init(
    STEEL_WALL_STRUCT *steelWall,
    int pos_x,
    int pos_y)
{
  steelWall->x = pos_x;
  steelWall->y = pos_y;
  steelWall->redraw = true;
}

/* desenha a parede de aço */
void steel_wall_draw(
    STEEL_WALL_STRUCT *steelWall,
    int *steelWallCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *steelWallCount; i++)
    if (steelWall[i].redraw) /* verifica se a parede de aço ainda esta no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->steel_wall,
          0, 0, STEEL_WALL_SPRITE_WIDTH, STEEL_WALL_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                               /* coloração da imagem */
          0, 0,                                                    /* centro de rotação */
          steelWall[i].x, steelWall[i].y,                          /* posição atual */
          STEEL_WALL_SCALE, STEEL_WALL_SCALE,                      /* escala */
          0, 0);
}

/* libera meória do vetor de paredes de aço */
void steel_wall_free(STEEL_WALL_STRUCT *steelWall)
{
  free(steelWall);
}