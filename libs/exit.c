#include "exit.h"

/* aloca memória para uma saída só */
EXIT_STRUCT *allocate_exit()
{
  return malloc(sizeof(EXIT_STRUCT));
}

/* inicializa a saída */
void exit_init(EXIT_STRUCT *exit, int pos_x, int pos_y)
{
  exit->x = pos_x;
  exit->y = pos_y;
  exit->source_x = EXIT_SPRITE_WIDTH;
  exit->source_y = 0;
  exit->redraw = false; /* incializa como falso, porque a saída so vai aparecer quando o herói pegar a quantidade necessária de diamantes */
}

/* atualiza as propriedades da saída */
void exit_update_properties(
    EXIT_STRUCT **exit,
    int pos_x,
    int pos_y,
    int source_x,
    int source_y,
    bool redraw)
{
  (*exit)->x = pos_x;
  (*exit)->y = pos_y;
  (*exit)->source_x = source_x;
  (*exit)->source_y = source_y;
  (*exit)->redraw = redraw;
}

/* atualiza o estado da saida */
void exit_update(
    EXIT_STRUCT *exit,
    ROCKFORD_STRUCT *rockford,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    long int count)
{
  if (is_space_rockford(map, exit->y / BLOCK_SIZE, exit->x / BLOCK_SIZE)) /* herói ganha */
  {
    exit->redraw = false;
    rockford->won = true;

    return;
  }

  if (
      rockford->quantity_of_diamonds >= EXIT_AMOUNT_NEEDED_TO_APPEAR &&
      !exit->redraw) /* herói atinge a quantidade de diamantes necessária para fazer aparecer a saída */
  {
    int randomLine = -1;
    int randomColumn = -1;

    while (
        randomLine == -1 &&
        randomColumn == -1) /* procura uma posição no mapa que seja vazia ou seja terra */
    {
      randomLine = generate_random_number_between(1, MAP_HEIGHT - 1);
      randomColumn = generate_random_number_between(1, MAP_WIDTH - 1);

      if (
          is_space_dirt(map, randomLine, randomColumn) ||
          is_space_empty(map, randomLine, randomColumn)) /* se for vazio ou terra */
        break;

      randomLine = -1;
      randomColumn = -1;
    }

    update_map_state(map, IS_EXIT, randomLine, randomColumn);

    exit_update_properties(
        &exit,
        randomColumn * BLOCK_SIZE,
        randomLine * BLOCK_SIZE,
        EXIT_SPRITE_WIDTH,
        0,
        true);
  }

  if (exit->redraw)
    if (count % UPDATE_SPEED == 0)  /* com intuito de reduzir a rapidez com que se atualiza a saída */
    {
      int exitWidth = al_get_bitmap_width(sprites->exit);

      exit->source_x += exitWidth / SUB_EXIT_SPRITE_QTD;

      if (exit->source_x >= exitWidth)
        exit->source_x = 0;
    }
}

/* desenha a saída */
void exit_draw(EXIT_STRUCT *exit, SPRITES_STRUCT *sprites)
{
  if (exit->redraw) /* verifica se a saída está no mapa */
    al_draw_tinted_scaled_rotated_bitmap_region(
        sprites->exit,
        exit->source_x, exit->source_y, EXIT_SPRITE_WIDTH, EXIT_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
        al_map_rgb(255, 255, 255),                                             /* coloração da imagem */
        0, 0,                                                                  /* centro de rotação da imagem */
        exit->x, exit->y,                                                      /* posição atual */
        EXIT_SCALE, EXIT_SCALE,                                                /* escale da imagem */
        0, 0);
}

/* libera memória da saída */
void exit_free(EXIT_STRUCT *exit)
{
  free(exit);
}