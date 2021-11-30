#include "butterfly.h"

/* aloca memória para o vetor de borboletas */
BUTTERFLY_STRUCT *allocate_array_butterfly(int butterflyCount)
{
  return (BUTTERFLY_STRUCT *)malloc(sizeof(BUTTERFLY_STRUCT) * butterflyCount);
}

/* inicializa a borboleta */
void butterfly_init(BUTTERFLY_STRUCT *butterfly, int pos_x, int pos_y)
{
  butterfly->x = pos_x;
  butterfly->y = pos_y;
  butterfly->source_x = BUTTERFLY_SPRITE_WIDTH;
  butterfly->source_y = 0;
  butterfly->direction = NO_DIRECTION;
  butterfly->redraw = true;
  butterfly->amount_of_diamonds = generate_random_number_between(0, 5);
}

/* move a borboleta para cima */
void move_butterfly_up(BUTTERFLY_STRUCT *butterfly)
{
  butterfly->y -= BLOCK_SIZE;
  butterfly->direction = UP;
}

/* move a borboleta para baixo */
void move_butterfly_down(BUTTERFLY_STRUCT *butterfly)
{
  butterfly->y += BLOCK_SIZE;
  butterfly->direction = DOWN;
}

//move a borboleta para a esquerda
void move_butterfly_left(BUTTERFLY_STRUCT *butterfly)
{
  butterfly->x -= BLOCK_SIZE;
  butterfly->direction = LEFT;
}

/* move a borboleta para a direita */
void move_butterfly_right(BUTTERFLY_STRUCT *butterfly)
{
  butterfly->x += BLOCK_SIZE;
  butterfly->direction = RIGHT;
}

/* verifica se o rockford ou a amoeba estão na redondeza */
bool verify_rockford_amoeba_presence_in_neighborhood_butterfly(BUTTERFLY_STRUCT *firefly, char map[MAP_HEIGHT][MAP_WIDTH])
{
  if (is_space_rockford(map, firefly->y / BLOCK_SIZE + 1, firefly->x / BLOCK_SIZE) ||
      is_space_amoeba(map, firefly->y / BLOCK_SIZE + 1, firefly->x / BLOCK_SIZE))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->y += BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (is_space_rockford(map, firefly->y / BLOCK_SIZE - 1, firefly->x / BLOCK_SIZE) ||
      is_space_amoeba(map, firefly->y / BLOCK_SIZE - 1, firefly->x / BLOCK_SIZE))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->y -= BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (is_space_rockford(map, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE + 1) ||
      is_space_amoeba(map, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE + 1))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->x += BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  if (is_space_rockford(map, (firefly->y / BLOCK_SIZE), (firefly->x / BLOCK_SIZE) - 1) ||
      is_space_amoeba(map, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE - 1))
  {
    update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    firefly->x -= BLOCK_SIZE;
    update_map_state(map, IS_FIREFLY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);
    return true;
  }

  return false;
}

/* gera o diamante e reseta os parametros */
void create_diamond_from_butterfly(DIAMOND_STRUCT **diamond, int pos_x, int pos_y)
{
  (*diamond)->x = pos_x;
  (*diamond)->y = pos_y;
  (*diamond)->source_x = DIAMOND_SPRITE_WIDTH;
  (*diamond)->source_y = 0;
  (*diamond)->redraw = true;
  (*diamond)->falling = false;
}

/* gera os diamantes após a morte da borboleta */
void generate_diamonds(
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH])
{
  DIAMOND_STRUCT *diamondTemp;
  int i = 0;

  while (i < butterfly->amount_of_diamonds)
  {
    diamondTemp = &diamond[*diamondCount];

    int randomLine = generate_random_number_between(1, MAP_HEIGHT - 1); /* por causa do placar */
    int randomColumn = generate_random_number_between(0, MAP_WIDTH - 1);

    if (
        is_space_dirt(map, randomLine, randomColumn) ||
        is_space_empty(map, randomLine, randomColumn))
    {
      (*diamondCount)++;
      update_map_state(map, IS_DIAMOND, randomLine, randomColumn);
      create_diamond_from_butterfly(&diamondTemp, randomColumn * BLOCK_SIZE, randomLine * BLOCK_SIZE);

      i++;
    }
  }

  butterfly->redraw = false;
}

/* cria uma explosão */
void create_explosion_butterfly(
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

/* atualiza o estado da borboleta */
void butterfly_update(
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *butterflyCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    SPRITES_STRUCT *sprites,
    long int count)
{
  BUTTERFLY_STRUCT *butterflyPtr;

  for (int i = 0; i < *butterflyCount; i++)
  {
    butterflyPtr = &butterfly[i];

    if (butterflyPtr->redraw) /* verifica que a borboleta ainda está no mapa */
    {
      if (is_space_empty(map, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE)) /* verifica se houve uma explosão na redondeza */
      {
        generate_diamonds(butterflyPtr, diamond, diamondCount, map);

        return;
      }

      if (!is_space_butterfly(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE))) /* verifica se a borboleta não ocupa o lugar que deveria ocupar. Isso ocorre, porque algo matou ela e ela explode */
      {
        int butterflyPtrLine = butterflyPtr->y / BLOCK_SIZE;
        int butterflyPtrColumn = butterflyPtr->x / BLOCK_SIZE;

        EXPLOSION_STRUCT *explosionPtr;
        int explosionCount = 0;

        for (int i = butterflyPtrLine - 1; i <= butterflyPtrLine + 1; i++)
          for (int j = butterflyPtrColumn - 1; j <= butterflyPtrColumn + 1; j++)
            if (!is_space_steel_wall(map, i, j) && !is_space_exit(map, i, j))
            {
              update_map_state(map, IS_EMPTY, i, j);

              explosionPtr = &explosion[explosionCount];

              create_explosion_butterfly(&explosionPtr, j * BLOCK_SIZE, i * BLOCK_SIZE);

              explosionCount++;
            }

        generate_diamonds(butterflyPtr, diamond, diamondCount, map);
        al_play_sample(audio->explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

        return;
      }

      if (count % UPDATE_SPEED == 0)
      {
        if (verify_rockford_amoeba_presence_in_neighborhood_butterfly(butterflyPtr, map))
          generate_diamonds(butterflyPtr, diamond, diamondCount, map);
        else
        {
          update_map_state(map, IS_EMPTY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);

          switch (butterflyPtr->direction)
          {
          case RIGHT:
            if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_down(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
              move_butterfly_right(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_up(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
              move_butterfly_left(butterflyPtr);
            break;
          case UP:
            if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
              move_butterfly_right(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_up(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
              move_butterfly_left(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_down(butterflyPtr);
            break;
          case LEFT:
            if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_up(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
              move_butterfly_left(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_down(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
              move_butterfly_right(butterflyPtr);
            break;
          case DOWN:
            if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
              move_butterfly_left(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_down(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
              move_butterfly_right(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_up(butterflyPtr);
            break;
          default:
            if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE + 1)))
              move_butterfly_right(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE + 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_down(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE - 1), (butterflyPtr->x / BLOCK_SIZE)))
              move_butterfly_up(butterflyPtr);
            else if (is_space_empty(map, (butterflyPtr->y / BLOCK_SIZE), (butterflyPtr->x / BLOCK_SIZE - 1)))
              move_butterfly_left(butterflyPtr);

            break;
          }

          update_map_state(map, IS_BUTTERFLY, butterflyPtr->y / BLOCK_SIZE, butterflyPtr->x / BLOCK_SIZE);
        }

        int butterflySpriteWidth = al_get_bitmap_width(sprites->butterfly);

        butterflyPtr->source_x += butterflySpriteWidth / SUB_BUTTERFLY_SPRITE_QTD;

        if (butterflyPtr->source_x >= butterflySpriteWidth) /* reseta animação */
          butterflyPtr->source_x = 0;
      }
    }
  }
}

/* função que desenha a borboleta */
void butterfly_draw(
    BUTTERFLY_STRUCT *butterfly,
    int *butterflyCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *butterflyCount; i++)
    if (butterfly[i].redraw) /* verifica se a borboleta ainda está no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->butterfly,
          butterfly[i].source_x, butterfly[i].source_y, BUTTERFLY_SPRITE_WIDTH, BUTTERFLY_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                                                                     /* coloração da imagem */
          0, 0,                                                                                          /* centro de rotação */
          butterfly[i].x, butterfly[i].y,                                                                /* posição atual */
          BUTTERFLY_SCALE, BUTTERFLY_SCALE,                                                              /* escala */
          0, 0);
}

/* libera o vetor de borboletas */
void butterfly_free(BUTTERFLY_STRUCT *butterfly)
{
  free(butterfly);
}