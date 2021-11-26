#include "brick-wall.h"

/* aloca memória para o vetor de paredes */
BRICK_WALL_STRUCT *allocate_array_brick_wall(int brickWallCount)
{
  return (BRICK_WALL_STRUCT *)malloc(sizeof(BRICK_WALL_STRUCT) * brickWallCount);
}

/* inicializa a parede */
void brick_wall_init(
    BRICK_WALL_STRUCT *brickWall,
    int pos_x,
    int pos_y)
{
  brickWall->x = pos_x;
  brickWall->y = pos_y;
  brickWall->redraw = true;
}

/* atualiza o estado da parede */
void brick_wall_update(
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    char map[MAP_HEIGHT][MAP_WIDTH])
{
  BRICK_WALL_STRUCT *brickWallPtr;

  for (int i = 0; i < *brickWallCount; i++) /* loop sobre o vetor de paredes */
  {
    brickWallPtr = &brickWall[i];

    if (brickWallPtr->redraw)                                                                    /* verifica se a parede ainda esta no mapa */
      if (!is_space_brick_wall(map, brickWallPtr->y / BLOCK_SIZE, brickWallPtr->x / BLOCK_SIZE)) /* verifica se a parede esta em um lugar que esta sendo ocupado por qualquer outra coisa, pois isso significa que houve uma explosão em sua redondeza */
        brickWallPtr->redraw = false;                                                            /* se o de cima for verdade, então para de desenhar a parede */
  }
}

/* desenha a parede */
void brick_wall_draw(
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *brickWallCount; i++)
    if (brickWall[i].redraw) /* verifica se a parede ainda esta no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->brick_wall,
          0, 0, BRICK_WALL_SPRITE_WIDTH, BRICK_WALL_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                               /* coloração da imagem */
          0, 0,                                                    /* centro de rotação da imagem */
          brickWall[i].x, brickWall[i].y,                          /* posição atual */
          BRICK_WALL_SCALE, BRICK_WALL_SCALE,                      /* escale da imagem */
          0, 0);
}

/* libera espaço da memória */
void brick_wall_free(BRICK_WALL_STRUCT *brickWall)
{
  free(brickWall);
}