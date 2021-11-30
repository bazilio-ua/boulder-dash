#include "amoeba.h"

/* aloca memória para vetor de amoebas */
AMOEBA_STRUCT *allocate_array_amoeba(int amoebaCount)
{
  return (AMOEBA_STRUCT *)calloc(amoebaCount, sizeof(AMOEBA_STRUCT));
}

/* inicializa amoeba */
void amoeba_init(
    AMOEBA_STRUCT *amoeba,
    int pos_x,
    int pos_y,
    int spawnedTime)
{
  amoeba->x = pos_x;
  amoeba->y = pos_y;
  amoeba->source_x = AMOEBA_SPRITE_WIDTH;
  amoeba->source_y = 0;
  amoeba->redraw = true;
  amoeba->spawned_time = spawnedTime;
  amoeba->last_time_grew_up = spawnedTime;
}

/* verifica se a amoeba está bloqueada em algum de seus lados */
bool is_amoeba_blocked(AMOEBA_STRUCT *amoeba, char map[MAP_HEIGHT][MAP_WIDTH])
{
  int amoebaLine = amoeba->y / BLOCK_SIZE;
  int amoebaColumn = amoeba->x / BLOCK_SIZE;

  int topLine = amoebaLine - 1;
  int topColumn = amoebaColumn;

  int rightLine = amoebaLine;
  int rightColumn = amoebaColumn + 1;

  int bottomLine = amoebaLine + 1;
  int bottomColumn = amoebaColumn;

  int leftLine = amoebaLine;
  int leftColumn = amoebaColumn - 1;

  if (!is_space_amoeba(map, topLine, topColumn) &&
      !is_space_boulder(map, topLine, topColumn) &&
      !is_space_steel_wall(map, topLine, topColumn) &&
      !is_space_brick_wall(map, topLine, topColumn))
    return false;

  if (!is_space_amoeba(map, rightLine, rightColumn) &&
      !is_space_boulder(map, rightLine, rightColumn) &&
      !is_space_steel_wall(map, rightLine, rightColumn) &&
      !is_space_brick_wall(map, rightLine, rightColumn))
    return false;

  if (!is_space_amoeba(map, bottomLine, bottomColumn) &&
      !is_space_boulder(map, bottomLine, bottomColumn) &&
      !is_space_steel_wall(map, bottomLine, bottomColumn) &&
      !is_space_brick_wall(map, bottomLine, bottomColumn))
    return false;

  if (!is_space_amoeba(map, leftLine, leftColumn) &&
      !is_space_boulder(map, leftLine, leftColumn) &&
      !is_space_steel_wall(map, leftLine, leftColumn) &&
      !is_space_brick_wall(map, leftLine, leftColumn))
    return false;

  return true;
}

/* cria uma explosão */
void create_explosion_amoeba(
    EXPLOSION_STRUCT **explosion,
    int pos_x,
    int pos_y)
{
  (*explosion)->x = pos_x;
  (*explosion)->y = pos_y;
  (*explosion)->source_x = 0;
  (*explosion)->source_y = 0;
  (*explosion)->redraw = true;
  (*explosion)->start = 0;
  (*explosion)->end = EXPLOSION_DURATION;
}

/* cria uma amoeba */
void create_amoeba(
    AMOEBA_STRUCT *amoeba,
    int pos_x,
    int pos_y,
    int time)
{
  amoeba->x = pos_x;
  amoeba->y = pos_y;
  amoeba->source_x = AMOEBA_SPRITE_WIDTH;
  amoeba->source_y = 0;
  amoeba->redraw = true;
  amoeba->spawned_time = time;
  amoeba->last_time_grew_up = time;
}

/* função que atualiza o estado da amoeba */
void amoeba_update(
    AMOEBA_STRUCT *amoeba,
    BOULDER_STRUCT *boulder,
    DIAMOND_STRUCT *diamond,
    int *amoebaCount,
    int *boulderCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    SPRITES_STRUCT *sprites,
    long int count)
{
  AMOEBA_STRUCT *amoebaPtr;
  bool isBlocked = true;
  int i, j, k;

  for (i = 0; i < *amoebaCount; i++)
  {
    amoebaPtr = &amoeba[i];

    if (amoebaPtr->redraw) /* verifica se a amoeba ainda está no mapa */
    {
      if (is_space_empty(map, amoebaPtr->y / BLOCK_SIZE, amoebaPtr->x / BLOCK_SIZE)) /* verifica se não houve uma explosão nas redondezas da amoeba */
      {
        amoebaPtr->redraw = false;
        return;
      }

      if (!is_space_amoeba(map, (amoebaPtr->y / BLOCK_SIZE), (amoebaPtr->x / BLOCK_SIZE))) /* verifica se a amoeba não ocupa de fato o seu lugar. Quando isso ocorre, significa que ela vai explodir */
      {
        int amoebaPtrLine = amoebaPtr->y / BLOCK_SIZE;
        int amoebaPtrColumn = amoebaPtr->x / BLOCK_SIZE;

        EXPLOSION_STRUCT *explosionPtr;
        int explosionCount = 0;

        for (j = amoebaPtrLine - 1; j <= amoebaPtrLine + 1; j++)
          for (k = amoebaPtrColumn - 1; k <= amoebaPtrColumn + 1; k++)
            if (!is_space_steel_wall(map, i, j) && !is_space_exit(map, i, j))
            {
              update_map_state(map, IS_EMPTY, j, k);

              explosionPtr = &explosion[explosionCount];

              create_explosion_amoeba(&explosionPtr, (k * BLOCK_SIZE), (j * BLOCK_SIZE));

              explosionCount++;
            }

        amoebaPtr->redraw = false;
        al_play_sample(audio->explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

        return;
      }

      if (isBlocked) /* verifica se a amoeba esta bloqueada. essa verificação é necessária, porque, desta forma, irei sabe se uma das amoebas não esta bloqueada e, sabendo disso, já posso afirmar que a amoeba inteira não está bloqueada e, portanto, não irá transformalas em diamante  */
        isBlocked = is_amoeba_blocked(amoebaPtr, map);

      if (count % UPDATE_SPEED == 0) /* reduz a rapized com que se atualiza a animação da amoeba */
      {
        int amoebaSpriteWidth = al_get_bitmap_width(sprites->amoeba);

        amoebaPtr->source_x += amoebaSpriteWidth / SUB_AMOEBA_SPRITE_QTD;

        if (amoebaPtr->source_x >= amoebaSpriteWidth)
          amoebaPtr->source_x = 0;
      }

      if (count - amoebaPtr->last_time_grew_up >= TIME_TO_GROW) /* verifica se a amoeba pode crescer */
      {
        int dirtLine = -1;
        int dirtColumn = -1;
        AMOEBA_STRUCT *amoebaTemp = &amoeba[*amoebaCount];

        amoebaPtr->last_time_grew_up = count;

        if (is_space_dirt(map, amoebaPtr->y / BLOCK_SIZE - 1, amoebaPtr->x / BLOCK_SIZE)) /* em cima */
        {
          dirtLine = amoebaPtr->y / BLOCK_SIZE - 1;
          dirtColumn = amoebaPtr->x / BLOCK_SIZE;
        }
        else if (is_space_dirt(map, amoebaPtr->y / BLOCK_SIZE, amoebaPtr->x / BLOCK_SIZE + 1)) /* direita */
        {
          dirtLine = amoebaPtr->y / BLOCK_SIZE;
          dirtColumn = amoebaPtr->x / BLOCK_SIZE + 1;
        }
        else if (is_space_dirt(map, amoebaPtr->y / BLOCK_SIZE + 1, amoebaPtr->x / BLOCK_SIZE)) /* baixo */
        {
          dirtLine = amoebaPtr->y / BLOCK_SIZE + 1;
          dirtColumn = amoebaPtr->x / BLOCK_SIZE;
        }
        else if (is_space_dirt(map, amoebaPtr->y / BLOCK_SIZE, amoebaPtr->x / BLOCK_SIZE - 1)) /* esquerda */
        {
          dirtLine = amoebaPtr->y / BLOCK_SIZE;
          dirtColumn = amoebaPtr->x / BLOCK_SIZE - 1;
        }

        if (dirtLine != -1 && dirtColumn != -1)
        {
          (*amoebaCount)++;
          update_map_state(map, IS_AMOEBA, dirtLine, dirtColumn);
          create_amoeba(amoebaTemp, dirtColumn * BLOCK_SIZE, dirtLine * BLOCK_SIZE, count);
        }
      }
    }
  }

  if (count - amoeba[0].spawned_time >= AMOEBA_LIFE_TIME) /* verifica se já passou o tempo de vida desde que a primeira amoeba foi criada */
  {
    BOULDER_STRUCT *boulderTemp;

    for (i = 0; i < *amoebaCount; i++)
    {
      amoebaPtr = &amoeba[i];

      if (amoebaPtr->redraw)
      {
        boulderTemp = &boulder[*boulderCount];

        int amoebaLine = amoebaPtr->y / BLOCK_SIZE;
        int amoebaColumn = amoebaPtr->x / BLOCK_SIZE;

        (*boulderCount)++;
        update_map_state(map, IS_BOULDER, amoebaLine, amoebaColumn);

        /* cria pedra */
        boulderTemp->x = amoebaColumn * BLOCK_SIZE;
        boulderTemp->y = amoebaLine * BLOCK_SIZE;
        boulderTemp->collision_time = 0;
        boulderTemp->redraw = true;
        boulderTemp->falling = false;
        amoebaPtr->redraw = false;
      }
    }
  }

  else if (isBlocked) /* se for true, signfica que todas as amoebas estão bloqueadas por uma outra amoeba, parede, parede de aço ou perdra. Desta forma, são gerados os diamantes */
  {
    DIAMOND_STRUCT *diamondTemp;

    for (i = 0; i < *amoebaCount; i++)
    {
      amoebaPtr = &amoeba[i];

      if (amoebaPtr->redraw)
      {
        diamondTemp = &diamond[*diamondCount];

        int amoebaLine = amoebaPtr->y / BLOCK_SIZE;
        int amoebaColumn = amoebaPtr->x / BLOCK_SIZE;

        (*diamondCount)++;
        update_map_state(map, IS_DIAMOND, amoebaLine, amoebaColumn);

        /* cria diamante */
        diamondTemp->x = amoebaColumn * BLOCK_SIZE;
        diamondTemp->y = amoebaLine * BLOCK_SIZE;
        diamondTemp->source_x = DIAMOND_SPRITE_WIDTH;
        diamondTemp->source_y = 0;
        diamondTemp->redraw = true;
        diamondTemp->falling = false;

        amoebaPtr->redraw = false;
      }
    }
  }
}

/* função que desenha amoeba */
void amoeba_draw(
    AMOEBA_STRUCT *amoeba,
    int *amoebaCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *amoebaCount; i++)
    if (amoeba[i].redraw) /* verifica se ainda está no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->amoeba,
          amoeba[i].source_x, amoeba[i].source_y, AMOEBA_SPRITE_WIDTH, AMOEBA_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                                                         /* coloração da imagem */
          0, 0,                                                                              /* centro de rotação */
          amoeba[i].x, amoeba[i].y,                                                          /* posição atual */
          AMOEBA_SCALE, AMOEBA_SCALE,                                                        /* escala */
          0, 0);
}

/* libera memoria do vetor de amoebas */
void amoeba_free(AMOEBA_STRUCT *amoeba)
{
  free(amoeba);
}