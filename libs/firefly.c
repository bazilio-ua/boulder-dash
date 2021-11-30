#include "firefly.h"

/* aloca memória para vetor de fireflyes */
FIREFLY_STRUCT *allocate_array_firefly(int fireflyCount)
{
  return (FIREFLY_STRUCT *)malloc(sizeof(FIREFLY_STRUCT) * fireflyCount);
}

/* inicializa firefly */
void firefly_init(FIREFLY_STRUCT *firefly, int pos_x, int pos_y)
{
  firefly->x = pos_x;
  firefly->y = pos_y;
  firefly->source_x = FIREFLY_SPRITE_WIDTH;
  firefly->source_y = 0;
  firefly->redraw = true;
  firefly->direction = NO_DIRECTION;
}

/* move o firefly para cima */
void move_firefly_up(FIREFLY_STRUCT *firefly)
{
  firefly->y -= BLOCK_SIZE;
  firefly->direction = UP;
}

/* move o firefly para baixo */
void move_firefly_down(FIREFLY_STRUCT *firefly)
{
  firefly->y += BLOCK_SIZE;
  firefly->direction = DOWN;
}

/* move firefly para a esquerda */
void move_firefly_left(FIREFLY_STRUCT *firefly)
{
  firefly->x -= BLOCK_SIZE;
  firefly->direction = LEFT;
}

/* move o firefly para a direita */
void move_firefly_right(FIREFLY_STRUCT *firefly)
{
  firefly->x += BLOCK_SIZE;
  firefly->direction = RIGHT;
}

/* verfica se o rockford ou a amoeba estão na redondeza */
bool verify_rockford_amoeba_presence_in_neighborhood_firefly(
    FIREFLY_STRUCT *firefly,
    char map[MAP_HEIGHT][MAP_WIDTH])
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

/* cria uma explosão */
void create_explosion_firefly(
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

/* atualiza o estado do firefly */
void firefly_update(
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    SPRITES_STRUCT *sprites,
    long int count)
{
  FIREFLY_STRUCT *fireflyPtr;

  for (int i = 0; i < *fireflyCount; i++)
  {
    fireflyPtr = &firefly[i];

    if (fireflyPtr->redraw) /* verifica se o firefly ainda está no mapa */
    {
      if (is_space_empty(map, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE)) /* se houve uma explosão na redondeza */
      {
        fireflyPtr->redraw = false;
        return;
      }

      else if (!isSpaceFirefly(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE))) /* se o firefly não ocupa o próprio espaço. Isso pode ocorrer quando algo o matou e esta para explodir */
      {
        int fireflyPtrLine = fireflyPtr->y / BLOCK_SIZE;
        int fireflyPtrColumn = fireflyPtr->x / BLOCK_SIZE;

        EXPLOSION_STRUCT *explosionPtr;
        int explosionCount = 0;

        for (int i = fireflyPtrLine - 1; i <= fireflyPtrLine + 1; i++)
          for (int j = fireflyPtrColumn - 1; j <= fireflyPtrColumn + 1; j++)
            if (!isSpaceSteelWall(map, i, j) && !isSpaceExit(map, i, j))
            {
              update_map_state(map, IS_EMPTY, i, j);

              explosionPtr = &explosion[explosionCount];

              create_explosion_firefly(&explosionPtr, j * BLOCK_SIZE, i * BLOCK_SIZE);

              explosionCount++;
            }

        al_play_sample(audio->explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        fireflyPtr->redraw = false;
      }

      else if (count % UPDATE_SPEED == 0)
      {
        if (verify_rockford_amoeba_presence_in_neighborhood_firefly(fireflyPtr, map))
          fireflyPtr->redraw = false;
        else
        {
          update_map_state(map, IS_EMPTY, firefly->y / BLOCK_SIZE, firefly->x / BLOCK_SIZE);

          switch (fireflyPtr->direction)
          {
          case RIGHT:
            if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_up(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
              move_firefly_right(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_down(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
              move_firefly_left(fireflyPtr);
            break;
          case UP:
            if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
              move_firefly_left(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_up(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
              move_firefly_right(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_down(fireflyPtr);
            break;
          case LEFT:
            if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_down(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
              move_firefly_left(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_up(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
              move_firefly_right(fireflyPtr);
            break;
          case DOWN:
            if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
              move_firefly_right(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_down(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
              move_firefly_left(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_up(fireflyPtr);
            break;
          default:
            if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE - 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_up(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE - 1)))
              move_firefly_left(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE + 1), (fireflyPtr->x / BLOCK_SIZE)))
              move_firefly_down(fireflyPtr);
            else if (is_space_empty(map, (fireflyPtr->y / BLOCK_SIZE), (fireflyPtr->x / BLOCK_SIZE + 1)))
              move_firefly_right(fireflyPtr);
            break;
          }

          update_map_state(map, IS_FIREFLY, fireflyPtr->y / BLOCK_SIZE, fireflyPtr->x / BLOCK_SIZE);
        }

        int fireflySpriteWidth = al_get_bitmap_width(sprites->firefly);

        fireflyPtr->source_x += fireflySpriteWidth / SUB_FIREFLY_SPRITE_QTD;

        if (fireflyPtr->source_x >= fireflySpriteWidth) /* reseta animação do firefly */
          fireflyPtr->source_x = 0;
      }
    }
  }
}

/* desenha firefly */
void firefly_draw(
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *fireflyCount; i++)
    if (firefly[i].redraw) /* verifica a existência do firefly */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->firefly,
          firefly[i].source_x, firefly[i].source_y, FIREFLY_SPRITE_WIDTH, FIREFLY_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                                                             /* coloração da imagem */
          0, 0,                                                                                  /* centro de rotação */
          firefly[i].x, firefly[i].y,                                                            /* posição atual */
          FIREFLY_SCALE, FIREFLY_SCALE,                                                          /* escala */
          0, 0);
}

/* libera memória do vetor de fireflyes */
void firefly_free(FIREFLY_STRUCT *firefly)
{
  free(firefly);
}