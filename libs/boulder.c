#include "boulder.h"

/* aloca memória para o vetor de pedras */
BOULDER_STRUCT *allocate_array_boulder(int boulderCount)
{
  return (BOULDER_STRUCT *)malloc(sizeof(BOULDER_STRUCT) * boulderCount);
}

/* inicializa a pedra */
void boulder_init(BOULDER_STRUCT *boulder, int pos_x, int pos_y)
{
  boulder->x = pos_x;
  boulder->y = pos_y;
  boulder->collision_time = 0;
  boulder->redraw = true;
  boulder->falling = false;
}

/* atualiza o estado da pedra */
void boulder_update(
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT *rockford,
    long int count)
{
  BOULDER_STRUCT *boulderPtr;

  for (int i = 0; i < *boulderCount; i++)
  {
    boulderPtr = &boulder[i];

    if (boulderPtr->redraw) /* verifica se a pedra ainda está no mapa */
    {
      if (!is_space_boulder(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE)) /* verifica se a pedra não ocupa de fato o seu devido lugar. Isso pode ocorrer quando ocorrer uma explosão nas redondezas */
      {
        boulderPtr->redraw = false; /* se o de cima é verdade, então para de desenhar esta pedra */
        return;
      }

      if (count % UPDATE_SPEED == 0) /* reduz a rapidez com que se atualiza o estado a pedra */
      {
        if (boulderPtr->falling &&                                                                 /* a pedra está caindo ?  */
            (is_space_rockford(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) || /* há um espaço com rockford 1 bloco a baixo ? */
             is_space_firefly(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||  /* há um espaço com fiefly 1 bloco a baixo ? */
             is_space_butterfly(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE))) /* há um espaço com butterfly 1 bloco a baixo ? */
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->y += BLOCK_SIZE; /* se o de cima for verdade então anda um espaço e mata */
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);

          return;
        }

        boulderPtr->falling = false;

        if (is_space_empty(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE)) /* verifica se há espaço vazio em baixo da pedra */
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->y += BLOCK_SIZE; /* se a verificação de cima for verdade, então a pedra cai um bloco */
          boulderPtr->falling = true;
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
        }
        else if (
            is_space_magic_wall(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) && /* magic wall está logo a baixo ? */
            (is_space_empty(map, boulderPtr->y / BLOCK_SIZE + 2, boulderPtr->x / BLOCK_SIZE) ||     /* há um espaço vazio dois blocos a baixo ? */
             is_space_butterfly(map, boulderPtr->y / BLOCK_SIZE + 2, boulderPtr->x / BLOCK_SIZE) || /* há um espaço com butterfly dois blocos a baixo ? */
             is_space_firefly(map, boulderPtr->y / BLOCK_SIZE + 2, boulderPtr->x / BLOCK_SIZE)))    /* há um espaço com firefly dois blocos a baixo ?*/
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->y += BLOCK_SIZE; /* se a verificação de cima for verdade, então a pedra cai um bloco */
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->falling = true;
        }
        else if (
            is_space_empty(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE - 1) &&   /* há um espaço vazio no bloco a esqueda em baixo ? */
            is_space_empty(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE - 1) &&       /* há um espaço vazio no bloco a esquerda ?  */
            (is_space_boulder(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||    /* há uma pedra no bloco a baixo ? */
             is_space_brick_wall(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) || /* há uma parede no bloco a baixo ? */
             is_space_diamond(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE)))     /* há um diamante no bloco a baixo ? */
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->x -= BLOCK_SIZE; /* se a verificação de cima for verdade, então anda para o lado esquerdo */
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
        }
        else if (
            is_space_empty(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE + 1) &&   /* há um espaço vazio no bloco a direita em baixo ? */
            is_space_empty(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE + 1) &&       /* há um espaço vazio no bloco a direita ? */
            (is_space_boulder(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) ||    /* há uma pedra no bloco a baixo ? */
             is_space_brick_wall(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE) || /* há uma parede no bloco a baixo ? */
             is_space_diamond(map, boulderPtr->y / BLOCK_SIZE + 1, boulderPtr->x / BLOCK_SIZE)))     /* há um diamante no bloco a baixo ? */
        {
          update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          boulderPtr->x += BLOCK_SIZE; /* se a verificação de cima for verdade, então anda para o lado direito */
          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
        }
        else if (
            is_space_rockford(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE + 1) && /* há um espaço com rockford na direita ? */
            rockford->active &&                                                                   /* rockford esta em movimento ? */
            rockford->direction == LEFT)                                                          /* a direção atual de rockford é para esquerda ? */
        {

          if (!boulderPtr->collision_time)      /* se não tiver em colisão ainda com o rockford, ou seja, collision_time ser zero */
            boulderPtr->collision_time = count; /* então atribui */

          if (count - boulderPtr->collision_time >= COLLISION_TIME_UNTIL_MOVE) /* se tiver passado o tempo */
          {
            update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
            update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);

            rockford->x -= ROCKFORD_SPEED;   /* move rockford para esquerda, sem atualizar o estado do mapa */
            boulderPtr->x -= ROCKFORD_SPEED; /* move pedra para esquerda, sem atualizar o estado do mapa */

            if (!is_space_empty(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE)) /* verifica se a posição atual na pedra é um espaço vazio ou não. Isso, porque se não for vazio significa que a pedra e o rockford precisam ficar na configuração anterior */
            {
              rockford->x += ROCKFORD_SPEED;   /* volta para configuração anteriro */
              boulderPtr->x += ROCKFORD_SPEED; /* volta para configuração anteriro */
            }

            boulderPtr->collision_time = count;
          }

          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        }

        else if (
            is_space_rockford(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE - 1) && /* há um espaço com rockford a esquerda ? */
            rockford->active &&                                                                   /* rockford esta em movimento ? */
            rockford->direction == RIGHT)                                                         /* rockford esta andando para direita ? */
        {

          if (!boulderPtr->collision_time)      /* se não tiver em colisão ainda com o rockford, ou seja, collision_time ser zero */
            boulderPtr->collision_time = count; /* então atribui */

          if (count - boulderPtr->collision_time >= COLLISION_TIME_UNTIL_MOVE) //1s
          {
            update_map_state(map, IS_EMPTY, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
            update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);

            rockford->x += ROCKFORD_SPEED;   /* move rockford para direita, sem atualizar o estado do mapa */
            boulderPtr->x += ROCKFORD_SPEED; /* move pedra para direita, sem atualizar o estado do mapa */

            if (!is_space_empty(map, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE)) /* verifica se a posição atual na pedra é um espaço vazio ou não. Isso, porque se não for vazio significa que a pedra e o rockford precisam ficar na configuração anterior */
            {
              rockford->x -= ROCKFORD_SPEED;   /* volta para configuração anteriro */
              boulderPtr->x -= ROCKFORD_SPEED; /* volta para configuração anteriro */
            }

            boulderPtr->collision_time = count;
          }

          update_map_state(map, IS_BOULDER, boulderPtr->y / BLOCK_SIZE, boulderPtr->x / BLOCK_SIZE);
          update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);
        }
        else
          boulderPtr->collision_time = 0;
      }
    }
  }
}

/* função que desenha a pedra */
void boulder_draw(
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *boulderCount; i++)
    if (boulder[i].redraw) /* verifica se a pedra ainda esta no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->boulder,
          0, 0, BOULDER_SPRITE_WIDTH, BOULDER_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                         /* coloração da imagem */
          0, 0,                                              /* centro de rotação */
          boulder[i].x, boulder[i].y,                        /* posição atual */
          BOULDER_SCALE, BOULDER_SCALE,                      /* escala */
          0, 0);
}

/* libera memória do vetor de pedras */
void boulder_free(BOULDER_STRUCT *boulder)
{
  free(boulder);
}