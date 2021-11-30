#include "rockford.h"

/* aloca memória para o rockford */
ROCKFORD_STRUCT *allocate_rockford()
{
  return malloc(sizeof(ROCKFORD_STRUCT));
}

/* inicializa o rockford */
void rockford_init(ROCKFORD_STRUCT *rockford, int pos_x, int pos_y)
{
  if (!rockford->lives) /* se não houver essa verificação o rockford vai receber 3 vidas quando der restart o game */
    rockford->lives = 3;

  rockford->x = pos_x;
  rockford->y = pos_y;
  rockford->source_x = ROCKFORD_SPRITE_WIDTH;
  rockford->source_y = 0;
  rockford->direction = NO_DIRECTION;
  rockford->last_direction = NO_DIRECTION;
  rockford->score = 0;
  rockford->quantity_of_diamonds = 0;
  rockford->won = false;
  rockford->lose = false;
  rockford->redraw = true;

  if (!rockford->is_easter_egg_active) /* se não houver essa verificação o rockford vai atrapalgar a lógica do easter egg */
  {
    rockford->is_easter_egg_active = false;
    rockford->started_time_easter_egg = 0;
  }
}

/* cria uma explosão */
void create_explosion_rockford(
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

/* atualiza o estado do rockford */
void rockford_update(
    ROCKFORD_STRUCT *rockford,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    unsigned char key[ALLEGRO_KEY_MAX],
    SPRITES_STRUCT *sprites,
    long int count)
{
  if (is_space_empty(map, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE)) /* verifica se houve uma explosão nas redondezas do rockford */
  {
    rockford->redraw = false;
    rockford->lives = rockford->lives - 1;

    return;
  }

  if (!is_space_rockford(map, (rockford->y / BLOCK_SIZE), (rockford->x / BLOCK_SIZE))) /* verifica se o rockford não ocupa seu próprio espaço. Isso acpontece quando ele tiver morrido e irá explodir */
  {
    int rockfordLine = rockford->y / BLOCK_SIZE;
    int rockfordColumn = rockford->x / BLOCK_SIZE;

    EXPLOSION_STRUCT *explosionPtr;
    int explosionCount = 0;

    for (int i = rockfordLine - 1; i <= rockfordLine + 1; i++)
      for (int j = rockfordColumn - 1; j <= rockfordColumn + 1; j++)
        if (!is_space_steel_wall(map, i, j) && !is_space_exit(map, i, j))
        {
          update_map_state(map, IS_EMPTY, i, j);

          explosionPtr = &explosion[explosionCount];

          create_explosion_rockford(&explosionPtr, j * BLOCK_SIZE, i * BLOCK_SIZE);

          explosionCount++;
        }

    rockford->lives = rockford->lives - 1;
    rockford->redraw = false;
    al_play_sample(audio->explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    if (rockford->lives == 0) /* perde */
      rockford->lose = true;
  }

  if (count % UPDATE_SPEED == 0) /* reduz a rapidez com que se atualiza a animação e os movimentos do rockford */
  {
    rockford->active = true;
    update_map_state(map, IS_EMPTY, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);

    if (key[ALLEGRO_KEY_LEFT]) /* anda para a esquerda */
    {
      int leftColumn = (rockford->x / BLOCK_SIZE) - 1;
      int leftLine = (rockford->y / BLOCK_SIZE);

      if (is_space_empty(map, leftLine, leftColumn) ||
          is_space_dirt(map, leftLine, leftColumn) ||
          is_space_diamond(map, leftLine, leftColumn) ||
          is_space_exit(map, leftLine, leftColumn))
        rockford->x -= ROCKFORD_SPEED;

      rockford->last_direction = rockford->direction;
      rockford->direction = LEFT;
    }
    else if (key[ALLEGRO_KEY_RIGHT]) /* anda para a direita */
    {
      int rightColumn = (rockford->x / BLOCK_SIZE) + 1;
      int rightLine = (rockford->y / BLOCK_SIZE);

      if (is_space_empty(map, rightLine, rightColumn) ||
          is_space_dirt(map, rightLine, rightColumn) ||
          is_space_diamond(map, rightLine, rightColumn) ||
          is_space_exit(map, rightLine, rightColumn))
        rockford->x += ROCKFORD_SPEED;

      rockford->last_direction = rockford->direction;
      rockford->direction = RIGHT;
    }
    else if (key[ALLEGRO_KEY_UP]) /* anda para cima */
    {
      int topLine = (rockford->y / BLOCK_SIZE) - 1;
      int topColumn = (rockford->x / BLOCK_SIZE);

      if (is_space_empty(map, topLine, topColumn) ||
          is_space_dirt(map, topLine, topColumn) ||
          is_space_diamond(map, topLine, topColumn) ||
          is_space_exit(map, topLine, topColumn))
        rockford->y -= ROCKFORD_SPEED;

      if (rockford->direction != DOWN && rockford->direction != UP)
        rockford->last_direction = rockford->direction;

      rockford->direction = UP;
    }
    else if (key[ALLEGRO_KEY_DOWN]) /* anda para baixo */
    {
      int bottomLine = (rockford->y / BLOCK_SIZE) + 1;
      int bottomColumn = (rockford->x / BLOCK_SIZE);

      if (is_space_empty(map, bottomLine, bottomColumn) ||
          is_space_dirt(map, bottomLine, bottomColumn) ||
          is_space_diamond(map, bottomLine, bottomColumn) ||
          is_space_exit(map, bottomLine, bottomColumn))
        rockford->y += ROCKFORD_SPEED;

      if (rockford->direction != DOWN && rockford->direction != UP) /* anda para cima */
        rockford->last_direction = rockford->direction;

      rockford->direction = DOWN;
    }
    else
      rockford->active = false;

    update_map_state(map, IS_ROCKFORD, rockford->y / BLOCK_SIZE, rockford->x / BLOCK_SIZE);

    if (rockford->active)
    {
      int rockfordRunningLeftSpriteWidth = al_get_bitmap_width(sprites->rockford_running_left);
      int rockfordRunningRightSpriteWidth = al_get_bitmap_width(sprites->rockford_running_right);

      al_play_sample(audio->steps, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      rockford->source_y = 0;

      if (rockford->direction == LEFT)
        rockford->source_x += rockfordRunningLeftSpriteWidth / SUB_ROCKFORD_SPRITE_QTD;
      else if (rockford->direction == RIGHT)
        rockford->source_x += rockfordRunningRightSpriteWidth / SUB_ROCKFORD_SPRITE_QTD;
      else if (
          (rockford->direction == UP ||
           rockford->direction == DOWN) &&
          rockford->last_direction == LEFT)
        rockford->source_x += rockfordRunningLeftSpriteWidth / SUB_ROCKFORD_SPRITE_QTD;
      else if (
          (rockford->direction == UP ||
           rockford->direction == DOWN) &&
          rockford->last_direction == RIGHT)
        rockford->source_x += rockfordRunningRightSpriteWidth / SUB_ROCKFORD_SPRITE_QTD;
      else
        rockford->source_x = ROCKFORD_SPRITE_WIDTH;

      if (
          rockford->source_x >= rockfordRunningLeftSpriteWidth &&
          (rockford->direction == LEFT ||
           rockford->direction == UP ||
           rockford->direction == DOWN))
        rockford->source_x = 0;
      else if (
          rockford->source_x >= rockfordRunningRightSpriteWidth &&
          (rockford->direction == RIGHT ||
           rockford->direction == UP ||
           rockford->direction == DOWN))
        rockford->source_x = 0;
    }
    else
    {
      int rockfordWaitingSpriteWidth = al_get_bitmap_width(sprites->rockford_waiting);
      int rockfordWaitingSpriteHeight = al_get_bitmap_height(sprites->rockford_waiting);

      rockford->source_x += rockfordWaitingSpriteWidth / SUB_ROCKFORD_SPRITE_QTD;

      if (rockford->source_x >= rockfordWaitingSpriteWidth)
      {
        rockford->source_y += rockfordWaitingSpriteHeight / SUB_ROCKFORD_SPRITE_HEIGHT_QTD; /* passa para a próxima linha do sprite */

        if (rockford->source_y > 64)
          rockford->source_y = 0;

        rockford->source_x = 0;
      }
    }
  }
}

/* desenha o rockford */
void rockford_draw(ROCKFORD_STRUCT *rockford, SPRITES_STRUCT *sprites)
{
  if (rockford->redraw) /* verifica se ainda está no mapa */
  {
    if (rockford->lives < 0) /* verifica se não perdeu */
      return;

    if (rockford->active)
    {
      if (
          rockford->direction == LEFT ||
          (rockford->last_direction == LEFT &&
           (rockford->direction == UP ||
            rockford->direction == DOWN))) /* animação para esquerda */
        al_draw_tinted_scaled_rotated_bitmap_region(
            sprites->rockford_running_left,
            rockford->source_x, rockford->source_y, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
            al_map_rgb(255, 255, 255),                                                             /* coloração da imagem */
            0, 0,                                                                                  /* centro de rotação */
            rockford->x, rockford->y,                                                              /* posição atual */
            ROCKFORD_SCALE, ROCKFORD_SCALE,                                                        /* escala */
            0, 0);
      else if (
          rockford->direction == RIGHT ||
          (rockford->last_direction == RIGHT &&
           (rockford->direction == UP ||
            rockford->direction == DOWN))) /* animação para direita */
        al_draw_tinted_scaled_rotated_bitmap_region(
            sprites->rockford_running_right,
            rockford->source_x, rockford->source_y, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
            al_map_rgb(255, 255, 255),                                                             /* coloração da imagem */
            0, 0,                                                                                  /* centro de rotação */
            rockford->x, rockford->y,                                                              /* posição atual */
            ROCKFORD_SCALE, ROCKFORD_SCALE,                                                        /* escala */
            0, 0);
      else /* sem animação */
        al_draw_tinted_scaled_rotated_bitmap_region(
            sprites->rockford,
            0, 0, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
            al_map_rgb(255, 255, 255),                           /* coloração da imagem */
            0, 0,                                                /* centro de rotação */
            rockford->x, rockford->y,                            /* posição atual */
            ROCKFORD_SCALE, ROCKFORD_SCALE,                      /* escala */
            0, 0);
    }
    else /* animação de esperando... */
      al_draw_tinted_scaled_rotated_bitmap_region(
          sprites->rockford_waiting,
          rockford->source_x, rockford->source_y, ROCKFORD_SPRITE_WIDTH, ROCKFORD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
          al_map_rgb(255, 255, 255),                                                             /* coloração da imagem */
          0, 0,                                                                                  /* centro de rotação */
          rockford->x, rockford->y,                                                              /* posição atual */
          ROCKFORD_SCALE, ROCKFORD_SCALE,                                                        /* escala */
          0, 0);
  }
}

void rockford_free(ROCKFORD_STRUCT *rockford)
{
  free(rockford);
}