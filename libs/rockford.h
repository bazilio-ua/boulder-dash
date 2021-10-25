#include "utils.h"

#define ROCKFORD_WIDTH 24
#define ROCKFORD_HEIGHT 30
#define ROCKFORD_SPEED 3
#define ROCKFORD_MAX_X (BUFFER_WIDTH - ROCKFORD_WIDTH)
#define ROCKFORD_MAX_Y (BUFFER_HEIGHT - ROCKFORD_HEIGHT)

typedef struct SPRITES_STRUCT
{
  ALLEGRO_BITMAP *_sheet;
  ALLEGRO_BITMAP *rockford;
} SPRITES_STRUCT;

typedef struct ROCKFORD_STRUCT
{
  int x, y;
  int lives;
  int respawn_timer;
  int invincible_timer;
} ROCKFORD_STRUCT;

void rockford_init(ROCKFORD_STRUCT *rockford); 

void rockford_update(ROCKFORD_STRUCT *rockford, unsigned char key[ALLEGRO_KEY_MAX]); 

void rockford_draw(ROCKFORD_STRUCT *rockford, SPRITES_STRUCT *sprites); 
