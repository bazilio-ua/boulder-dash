#ifndef _UTILSH_
#define _UTILSH_

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <time.h>

#define KEY_SEEN 1
#define KEY_RELEASED 2

#define BUFFER_WIDTH 320
#define BUFFER_HEIGHT 160
#define DISPLAY_SCALE 4
#define BLOCK_SIZE 16
#define DISPLAY_WIDTH (BUFFER_WIDTH * DISPLAY_SCALE)
#define DISPLAY_HEIGHT (BUFFER_HEIGHT * DISPLAY_SCALE)

#define ROCKFORD_SPRITE_WIDTH 32
#define ROCKFORD_SPRITE_HEIGHT 32
#define ROCKFORD_SCALE 0.5
#define ROCKFORD_SPEED 16
#define NO_DIRECTION -1
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

#define DIAMOND_SPRITE_WIDTH 32
#define DIAMOND_SPRITE_HEIGHT 32
#define DIAMOND_SCALE 0.5
#define DIAMOND_SCORE 10

#define FIREFLY_SPRITE_WIDTH 32
#define FIREFLY_SPRITE_HEIGHT 32
#define FIREFLY_SCALE 0.5

#define AMOEBA_SPRITE_WIDTH 32
#define AMOEBA_SPRITE_HEIGHT 32
#define AMOEBA_SCALE 0.5
#define TIME_TO_GROW 300
#define AMOEBA_LIFE_TIME 3600

#define BUTTERFLY_SPRITE_WIDTH 32
#define BUTTERFLY_SPRITE_HEIGHT 32
#define BUTTERFLY_SCALE 0.5

#define SUB_EXIT_SPRITE_QTD 3  
#define EXIT_SPRITE_WIDTH 32
#define EXIT_SPRITE_HEIGHT 32
#define EXIT_SCALE 0.5
#define EXIT_AMOUNT_NEEDED_TO_APPEAR 5

#define MAGIC_WALL_SPRITE_WIDTH 32
#define MAGIC_WALL_SPRITE_HEIGHT 32
#define MAGIC_WALL_SCALE 0.5
#define ACTIVE_DURATION 300

#define STEEL_WALL_SPRITE_WIDTH 32
#define STEEL_WALL_SPRITE_HEIGHT 32
#define STEEL_WALL_SCALE 0.5

#define BOULDER_SPRITE_WIDTH 32
#define BOULDER_SPRITE_HEIGHT 32
#define BOULDER_SCALE 0.5

#define DIRT_SPRITE_WIDTH 32
#define DIRT_SPRITE_HEIGHT 32
#define DIRT_SCALE 0.5

#define BRICK_WALL_SPRITE_WIDTH 32
#define BRICK_WALL_SPRITE_HEIGHT 32
#define BRICK_WALL_SCALE 0.5

#define SUB_EXPLOSION_SPRITE_QTD 5
#define EXPLOSION_SPRITE_WIDTH 32
#define EXPLOSION_SPRITE_HEIGHT 32
#define EXPLOSION_SCALE 0.5
#define EXPLOSION_COUNT 9
#define EXPLOSION_DURATION 40

#define SCOREBOARD_SPRITE_WIDTH 32
#define SCOREBOARD_SPRITE_HEIGHT 16
#define SCOREBOARD_WIDTH_SCALE 0.5
#define SCOREBOARD_HEIGHT_SCALE 1

#define MAP_WIDTH 20
#define MAP_HEIGHT 10
#define MAX_SAMPLES 128

#define MAX_OBJECT_QUANTITY MAP_WIDTH *MAP_HEIGHT

#define EASTER_EGG_TIME 13620

#define UPDATE_SPEED 5

#define IS_EMPTY 'E'
#define IS_DIAMOND '0'
#define IS_DIRT '1'
#define IS_BOULDER '2'
#define IS_STEEL_WALL '3'
#define IS_BRICK_WALL '4'
#define IS_MAGIC_WALL '5'
#define IS_FIREFLY '6'
#define IS_BUTTERFLY '7'
#define IS_AMOEBA '8'
#define IS_EXIT '9'
#define IS_ROCKFORD 'R'

void initialize(bool isInitialized, const char *description);

//function to detect collision between two coordinates (x1,y1) and (x2,y2)
bool isCollision(int x1, int y1, int x2, int y2);

void update_map_state(char map[MAP_HEIGHT][MAP_WIDTH], char updatedState, int i, int j);

bool isSpaceEmpty(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool is_space_empty(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j);

bool isSpaceDirt(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool is_space_dirt(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j);

bool isSpaceDiamond(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool isSpaceBoulder(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool isSpaceRockford(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool is_space_rockford(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j);

bool isSpaceBrickWall(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool is_space_brick_wall(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j);

bool isSpaceSteelWall(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool isSpaceFirefly(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool isSpaceButterfly(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool isSpaceAmoeba(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool isSpaceMagicWall(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

bool isSpaceExit(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j);

int generateRandomNumberBetween(int lower, int upper);

int generate_random_number_between(
    int lower,
    int upper);

#endif
