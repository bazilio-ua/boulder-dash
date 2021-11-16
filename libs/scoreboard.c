#include "scoreboard.h"

void draw_scoreboard(
    ROCKFORD_STRUCT *rockford,
    SPRITES_STRUCT *sprites)
{
  int quantityOfDiamondsAux = rockford->quantity_of_diamonds;
  int diamondsUnity;
  int diamondsTens;

  int scoreAux = rockford->score;
  int scoreUnity;
  int scoreTens;
  int scoreHundreds;
  int scoreThousands;
  int scoreTensOfThousands;

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
      32, (diamondsTens)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                      // color, just use white if you don't want a tint
      0, 0,                                                                                           // center of rotation/scaling
      0, 0,                                                                                           // destination
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                // scale
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      32, (diamondsUnity)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                       // color, just use white if you don't want a tint
      0, 0,                                                                                            // center of rotation/scaling
      BLOCK_SIZE, 0,                                                                                   // destination
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                 // scale
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreUnity)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                   // color, just use white if you don't want a tint
      0, 0,                                                                                        // center of rotation/scaling
      (MAP_WIDTH - 1) * BLOCK_SIZE, 0,                                                             // destination
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                             // scale
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreTens)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                  // color, just use white if you don't want a tint
      0, 0,                                                                                       // center of rotation/scaling
      (MAP_WIDTH - 2) * BLOCK_SIZE, 0,                                                            // destination
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                            // scale
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreHundreds)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                      // color, just use white if you don't want a tint
      0, 0,                                                                                           // center of rotation/scaling
      (MAP_WIDTH - 3) * BLOCK_SIZE, 0,                                                                // destination
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                // scale
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreThousands)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                       // color, just use white if you don't want a tint
      0, 0,                                                                                            // center of rotation/scaling
      (MAP_WIDTH - 4) * BLOCK_SIZE, 0,                                                                 // destination
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                 // scale
      0, 0);

  al_draw_tinted_scaled_rotated_bitmap_region(
      sprites->scoreboard,
      0, (scoreTensOfThousands)*SCOREBOARD_SPRITE_HEIGHT, SCOREBOARD_SPRITE_WIDTH, SCOREBOARD_SPRITE_HEIGHT, // source bitmap region
      al_map_rgb(255, 255, 255),                                                                             // color, just use white if you don't want a tint
      0, 0,                                                                                                  // center of rotation/scaling
      (MAP_WIDTH - 5) * BLOCK_SIZE, 0,                                                                       // destination
      SCOREBOARD_WIDTH_SCALE, SCOREBOARD_HEIGHT_SCALE,                                                       // scale
      0, 0);
}