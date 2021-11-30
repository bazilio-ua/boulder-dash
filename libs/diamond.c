#include "diamond.h"

/* aloca memória para o vetor de diamantes */
DIAMOND_STRUCT *allocate_array_diamond(int diamondCount)
{
  return (DIAMOND_STRUCT *)malloc(sizeof(DIAMOND_STRUCT) * diamondCount);
}

/* inicializa o diamante */
void diamond_init(DIAMOND_STRUCT *diamond, int pos_x, int pos_y)
{
  diamond->x = pos_x;
  diamond->y = pos_y;
  diamond->source_x = DIAMOND_SPRITE_WIDTH;
  diamond->source_y = 0;
  diamond->redraw = true;
  diamond->falling = false;
}

/* atualiza o estado do diamante */
void diamond_update(
    DIAMOND_STRUCT *diamond,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    ROCKFORD_STRUCT *rockford,
    long int count)
{
  DIAMOND_STRUCT *diamondPtr;

  for (int i = 0; i < *diamondCount; i++)
  {
    diamondPtr = &diamond[i];

    if (diamondPtr->redraw) /* verifica se o diamante ainda está no mapa */
    {
      if (is_space_rockford(map, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE)) /* se o rockford pegou o diamante */
      {
        rockford->quantity_of_diamonds++;
        rockford->score += DIAMOND_SCORE;
        diamondPtr->redraw = false;

        return;
      }

      if (!is_space_diamond(map, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE)) /* se houve uma explosão na redondeza */
      {
        diamondPtr->redraw = false;

        return;
      }

      if (count % UPDATE_SPEED == 0) /* reduz a rapidez com que se atualiza o estado do diamante */
      {

        if (diamondPtr->falling &&                                                                 /* a diamante está caindo ?  */
            (is_space_rockford(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE) || /* há um espaço com rockford 1 bloco a baixo ? */
             is_space_firefly(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE) ||  /* há um espaço com fiefly 1 bloco a baixo ? */
             is_space_butterfly(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE))) /* há um espaço com butterfly 1 bloco a baixo ? */
        {
          update_map_state(map, IS_EMPTY, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE);
          diamondPtr->y += BLOCK_SIZE; /* se o de cima for verdade então anda um espaço e mata */
          update_map_state(map, IS_DIAMOND, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE);
          return;
        }

        diamondPtr->falling = false;

        if (is_space_empty(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE)) /* verifica se há espaço vazio em baixo da diamante */
        {
          update_map_state(map, IS_EMPTY, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE);
          diamondPtr->y += BLOCK_SIZE; /* se a verificação de cima for verdade, então a diamante cai um bloco */
          diamondPtr->falling = true;
          update_map_state(map, IS_DIAMOND, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE);
        }
        else if (
            is_space_empty(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE - 1) &&   /* há um espaço vazio no bloco a esqueda em baixo ? */
            is_space_empty(map, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE - 1) &&       /* há um espaço vazio no bloco a esquerda ?  */
            (is_space_boulder(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE) ||    /* há uma diamante no bloco a baixo ? */
             is_space_brick_wall(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE) || /* há uma parede no bloco a baixo ? */
             is_space_diamond(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE)))     /* há um diamante no bloco a baixo ? */
        {
          update_map_state(map, IS_EMPTY, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE);
          diamondPtr->x -= BLOCK_SIZE; /* se a verificação de cima for verdade, então anda para o lado esquerdo */
          update_map_state(map, IS_DIAMOND, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE);
        }
        else if (
            is_space_empty(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE + 1) &&   /* há um espaço vazio no bloco a direita em baixo ? */
            is_space_empty(map, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE + 1) &&       /* há um espaço vazio no bloco a direita ? */
            (is_space_boulder(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE) ||    /* há uma diamante no bloco a baixo ? */
             is_space_brick_wall(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE) || /* há uma parede no bloco a baixo ? */
             is_space_diamond(map, diamondPtr->y / BLOCK_SIZE + 1, diamondPtr->x / BLOCK_SIZE)))     /* há um diamante no bloco a baixo ? */
        {
          update_map_state(map, IS_EMPTY, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE);
          diamondPtr->x += BLOCK_SIZE; /* se a verificação de cima for verdade, então anda para o lado direito */
          update_map_state(map, IS_DIAMOND, diamondPtr->y / BLOCK_SIZE, diamondPtr->x / BLOCK_SIZE);
        }

        int diamondSpriteWidth = al_get_bitmap_width(sprites->diamond);

        diamondPtr->source_x += diamondSpriteWidth / SUB_DIAMOND_SPRITE_QTD; /* atualiza a animação */

        if (diamondPtr->source_x >= diamondSpriteWidth) /* reseta a animação */
          diamondPtr->source_x = 0;
      }
    }
  }
}

/* desenha as diamantes */
void diamond_draw(
    DIAMOND_STRUCT *diamond,
    int *diamondCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *diamondCount; i++)
    if (diamond[i].redraw) /* verifica se o diamante ainda está no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->diamond,
          diamond[i].source_x, diamond[i].source_y, DIAMOND_SPRITE_WIDTH, DIAMOND_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                                                             /* coloração da imagem */
          0, 0,                                                                                  /* centro de rotação */
          diamond[i].x, diamond[i].y,                                                            /* posição atual */
          DIAMOND_SCALE, DIAMOND_SCALE,                                                          /* escala */
          0, 0);
}

/* libera o vetor de diamantes */
void diamond_free(DIAMOND_STRUCT *diamond)
{
  free(diamond);
}