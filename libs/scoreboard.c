#include "scoreboard.h"

/* Desenha o placar */
void draw_scoreboard(
    ROCKFORD_STRUCT *rockford,
    SPRITES_STRUCT *sprites)
{
  int quantityOfDiamondsAux = rockford->quantity_of_diamonds;
  int diamondsUnity; /* Quantidade de diamantes por unidade */
  int diamondsTens;  /* Quantidade de diamantes por dezena */

  int scoreAux = rockford->score;
  int scoreUnity;           /* Pontuação por unidade */
  int scoreTens;            /* Pontuação por dezena */
  int scoreHundreds;        /* Pontuação por centena */
  int scoreThousands;       /* Pontuação por milhar */
  int scoreTensOfThousands; /* Pontuação por dezena de milhar */

  diamondsUnity = quantityOfDiamondsAux % 10;
  quantityOfDiamondsAux = quantityOfDiamondsAux / 10;
  diamondsTens = quantityOfDiamondsAux % 10;

  scoreUnity = scoreAux % 10;
  scoreAux = scoreAux / 10;
  scoreTens = scoreAux % 10;
  scoreAux = scoreAux / 10;
  scoreHundreds = scoreAux % 10;
  scoreAux = scoreAux / 10;
  scoreThousands = scoreAux % 10;
  scoreAux = scoreAux / 10;
  scoreTensOfThousands = scoreAux % 10;

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      32, (diamondsTens)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
      al_map_rgb(255, 255, 255),                                                                      /* coloração da imagem */
      0, 0,                                                                                           /* centro de rotação */
      0, 0,                                                                                           /* posição atual */
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                /* escala */
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      32, (diamondsUnity)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
      al_map_rgb(255, 255, 255),                                                                       /* coloração da imagem */
      0, 0,                                                                                            /* centro de rotação */
      BLOCK_SIZE, 0,                                                                                   /* posição atual */
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                 /* escala */
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreUnity)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
      al_map_rgb(255, 255, 255),                                                                   /* coloração da imagem */
      0, 0,                                                                                        /* centro de rotação */
      (MAP_WIDTH - 1) * BLOCK_SIZE, 0,                                                             /* posição atual */
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                             /* escala */
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreTens)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
      al_map_rgb(255, 255, 255),                                                                  /* coloração da imagem */
      0, 0,                                                                                       /* centro de rotação */
      (MAP_WIDTH - 2) * BLOCK_SIZE, 0,                                                            /* posição atual */
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                            /* escala */
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreHundreds)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
      al_map_rgb(255, 255, 255),                                                                      /* coloração da imagem */
      0, 0,                                                                                           /* centro de rotação */
      (MAP_WIDTH - 3) * BLOCK_SIZE, 0,                                                                /* posição atual */
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                /* escala */
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreThousands)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
      al_map_rgb(255, 255, 255),                                                                       /* coloração da imagem */
      0, 0,                                                                                            /* centro de rotação */
      (MAP_WIDTH - 4) * BLOCK_SIZE, 0,                                                                 /* posição atual */
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                 /* escala */
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreTensOfThousands)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, /* região de bitmap de origem até o fim. x_ini, y_ini, x_fim, y_fim */
      al_map_rgb(255, 255, 255),                                                                             /* coloração da imagem */
      0, 0,                                                                                                  /* centro de rotação */
      (MAP_WIDTH - 5) * BLOCK_SIZE, 0,                                                                       /* posição atual */
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                       /* escala */
      0, 0);
}