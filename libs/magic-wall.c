#include "magic-wall.h"

/* aloca memória para vetor de paredes mágicas */
MAGIC_WALL_STRUCT *allocate_array_magic_wall(int magicWallCount)
{
  return (MAGIC_WALL_STRUCT *)malloc(sizeof(MAGIC_WALL_STRUCT) * magicWallCount);
}

/* inicializa as paredes mágicas */
void magic_wall_init(MAGIC_WALL_STRUCT *magicWall, int pos_x, int pos_y)
{
  magicWall->x = pos_x;
  magicWall->y = pos_y;
  magicWall->source_x = 0;
  magicWall->source_y = 0;
  magicWall->redraw = true;
  magicWall->isActive = false;
  magicWall->activeStartTime = 0;
}

/* função que vai ativar a animação de todas as paredes mágica */
void active_all_magic_walls(
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount,
    int startTime)
{
  MAGIC_WALL_STRUCT *magicWallPtr;

  for (int i = 0; i < *magicWallCount; i++)
  {
    magicWallPtr = &magicWall[i];

    magicWallPtr->isActive = true,
    magicWallPtr->activeStartTime = startTime;
  }
}

/* função que vai desativar a animação de todas paredes mágicas */
void desactive_all_magic_walls(
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount)
{
  MAGIC_WALL_STRUCT *magicWallPtr;

  for (int i = 0; i < *magicWallCount; i++)
  {
    magicWallPtr = &magicWall[i];

    magicWallPtr->isActive = false;
    magicWallPtr->source_x = 0;
    magicWallPtr->activeStartTime = 0;
  }
}

/* gera o diamante e reseta os parametros */
void create_diamond_from_magic_wall(DIAMOND_STRUCT **diamond, int pos_x, int pos_y)
{
  (*diamond)->x = pos_x;
  (*diamond)->y = pos_y;
  (*diamond)->source_x = DIAMOND_SPRITE_WIDTH;
  (*diamond)->source_y = 0;
  (*diamond)->redraw = true;
  (*diamond)->falling = false;
}

/* função que atualiza o estado da parede mágica */
void magic_wall_update(
    MAGIC_WALL_STRUCT *magicWall,
    DIAMOND_STRUCT *diamond,
    int *magicWallCount,
    int *diamondCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    long int count)
{
  MAGIC_WALL_STRUCT *magicWallPtr;

  for (int i = 0; i < *magicWallCount; i++)
  {
    magicWallPtr = &magicWall[i];

    if (magicWallPtr->redraw) /* verifica se a parede mágica ainda está no mapa */
    {
      if (is_space_boulder(map, magicWallPtr->y / BLOCK_SIZE, magicWallPtr->x / BLOCK_SIZE)) /* verifica se a parede mágica está ocupando um lugar de uma pedra. Isso signifca que a pedra está prestes a ser transformada em diamante */
      {
        DIAMOND_STRUCT *diamondTemp;

        update_map_state(map, IS_MAGIC_WALL, magicWallPtr->y / BLOCK_SIZE, magicWallPtr->x / BLOCK_SIZE);
        active_all_magic_walls(magicWall, magicWallCount, count);

        diamondTemp = &diamond[*diamondCount];

        int magicWallLine = magicWallPtr->y / BLOCK_SIZE + 1;
        int magicWallColum = magicWallPtr->x / BLOCK_SIZE;

        (*diamondCount)++;
        update_map_state(map, IS_DIAMOND, magicWallLine, magicWallColum);
        create_diamond_from_magic_wall(&diamondTemp, magicWallColum * BLOCK_SIZE, magicWallLine * BLOCK_SIZE);

        return;
      }

      if (!is_space_magic_wall(map, magicWallPtr->y / BLOCK_SIZE, magicWallPtr->x / BLOCK_SIZE)) /* se houve uma explosão nas redondezas */
      {
        magicWallPtr->redraw = false;
        return;
      }

      if (count % UPDATE_SPEED == 0) /* reduz a rapidez com que atualiza a animação da parede mágica */
      {
        int magicWallBitmapWidth = al_get_bitmap_width(sprites->magic_wall);

        if (magicWallPtr->isActive) /* verifica se a parede mágica está ativa */
        {
          magicWallPtr->source_x += magicWallBitmapWidth / SUB_MAGIC_WALL_SPRITE_QTD;

          if (count - magicWall->activeStartTime >= ACTIVE_DURATION)
            desactive_all_magic_walls(magicWall, magicWallCount);
        }

        if (magicWallPtr->source_x >= magicWallBitmapWidth) /* reseta a animação */
          magicWallPtr->source_x = 0;
      }
    }
  }
}

/* função que desenha as paredes mágicas */
void magic_wall_draw(
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount,
    SPRITES_STRUCT *sprites)
{
  for (int i = 0; i < *magicWallCount; i++)
    if (magicWall[i].redraw) /* verifica se a parede mágica ainda está no mapa */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->magic_wall,
          magicWall[i].source_x, magicWall[i].source_y, MAGIC_WALL_SPRITE_WIDTH, MAGIC_WALL_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                                                                       /* coloração da imagem */
          0, 0,                                                                                            /* centro de rotação */
          magicWall[i].x, magicWall[i].y,                                                                  /* posição atual */
          MAGIC_WALL_SCALE, MAGIC_WALL_SCALE,                                                              /* escala */
          0, 0);
}

/* libera memória do vetor de paredes mágicas */
void magic_wall_free(MAGIC_WALL_STRUCT *magicWall)
{
  free(magicWall);
}