#ifndef _GAMEH_
#define _GAMEH_

#include "utils.h"
#include "rockford.h"
#include "diamond.h"
#include "firefly.h"
#include "amoeba.h"
#include "butterfly.h"
#include "exit.h"
#include "magic-wall.h"
#include "steel-wall.h"
#include "boulder.h"
#include "dirt.h"
#include "brick-wall.h"
#include "map.h"
#include "explosion.h"
#include "utils.h"
#include "scoreboard.h"
#include "audio.h"
#include "sprite.h"
#include "display.h"
#include "keyboard.h"

void game_initialization(
    unsigned char key[ALLEGRO_KEY_MAX],
    ALLEGRO_TIMER **timer,
    ALLEGRO_EVENT_QUEUE **queue,
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    AUDIO_STRUCT *audio,
    ROCKFORD_STRUCT **rockford,
    EXIT_STRUCT **exit,
    FIREFLY_STRUCT **firefly,
    int *fireflyCount,
    STEEL_WALL_STRUCT **steelWall,
    int *steelWallCount,
    BRICK_WALL_STRUCT **brickWall,
    int *brickWallCount,
    BOULDER_STRUCT **boulder,
    int *boulderCount,
    BUTTERFLY_STRUCT **butterfly,
    int *butterflyCount,
    DIRT_STRUCT **dirt,
    int *dirtCount,
    DIAMOND_STRUCT **diamond,
    int *diamondCount,
    AMOEBA_STRUCT **amoeba,
    int *amoebaCount,
    MAGIC_WALL_STRUCT **magicWall,
    int *magicWallCount,
    EXPLOSION_STRUCT **explosion);

void game_restart(
    bool *restart,
    int count,
    char map[MAP_HEIGHT][MAP_WIDTH],
    ROCKFORD_STRUCT **rockford,
    EXIT_STRUCT **exit,
    FIREFLY_STRUCT **firefly,
    int *fireflyCount,
    STEEL_WALL_STRUCT **steelWall,
    int *steelWallCount,
    BRICK_WALL_STRUCT **brickWall,
    int *brickWallCount,
    BOULDER_STRUCT **boulder,
    int *boulderCount,
    BUTTERFLY_STRUCT **butterfly,
    int *butterflyCount,
    DIRT_STRUCT **dirt,
    int *dirtCount,
    DIAMOND_STRUCT **diamond,
    int *diamondCount,
    AMOEBA_STRUCT **amoeba,
    int *amoebaCount,
    MAGIC_WALL_STRUCT **magicWall,
    int *magicWallCount,
    EXPLOSION_STRUCT **explosion);

void game_update(
    unsigned char key[ALLEGRO_KEY_MAX],
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    char map[MAP_HEIGHT][MAP_WIDTH],
    EXPLOSION_STRUCT *explosion,
    AUDIO_STRUCT *audio,
    SPRITES_STRUCT *sprites,
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *butterflyCount,
    int *diamondCount,
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    ROCKFORD_STRUCT *rockford,
    AMOEBA_STRUCT *amoeba,
    int *amoebaCount,
    DIRT_STRUCT *dirt,
    int *dirtCount,
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount,
    EXIT_STRUCT *exit,
    long int count,
    bool *restart,
    bool *done);

void handle_game(
    unsigned char key[ALLEGRO_KEY_MAX],
    ALLEGRO_EVENT *event,
    ALLEGRO_EVENT_QUEUE **queue,
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer,
    char map[MAP_HEIGHT][MAP_WIDTH],
    SPRITES_STRUCT *sprites,
    AUDIO_STRUCT *audio,
    ROCKFORD_STRUCT **rockford,
    EXIT_STRUCT **exit,
    FIREFLY_STRUCT **firefly,
    int *fireflyCount,
    STEEL_WALL_STRUCT **steelWall,
    int *steelWallCount,
    BRICK_WALL_STRUCT **brickWall,
    int *brickWallCount,
    BOULDER_STRUCT **boulder,
    int *boulderCount,
    BUTTERFLY_STRUCT **butterfly,
    int *butterflyCount,
    DIRT_STRUCT **dirt,
    int *dirtCount,
    DIAMOND_STRUCT **diamond,
    int *diamondCount,
    AMOEBA_STRUCT **amoeba,
    int *amoebaCount,
    MAGIC_WALL_STRUCT **magicWall,
    int *magicWallCount,
    EXPLOSION_STRUCT **explosion,
    bool *restart,
    bool *done);

void game_draw(
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer,
    FIREFLY_STRUCT *firefly,
    int *fireflyCount,
    EXPLOSION_STRUCT *explosion,
    SPRITES_STRUCT *sprites,
    BUTTERFLY_STRUCT *butterfly,
    DIAMOND_STRUCT *diamond,
    int *butterflyCount,
    int *diamondCount,
    BOULDER_STRUCT *boulder,
    int *boulderCount,
    ROCKFORD_STRUCT *rockford,
    AMOEBA_STRUCT *amoeba,
    int *amoebaCount,
    DIRT_STRUCT *dirt,
    int *dirtCount,
    BRICK_WALL_STRUCT *brickWall,
    int *brickWallCount,
    MAGIC_WALL_STRUCT *magicWall,
    int *magicWallCount,
    STEEL_WALL_STRUCT *steelWall,
    int *steelWallCount,
    EXIT_STRUCT *exit);

void game_clear(
    ALLEGRO_TIMER **timer,
    ALLEGRO_EVENT_QUEUE **queue,
    ALLEGRO_DISPLAY **display,
    ALLEGRO_BITMAP **buffer,
    FIREFLY_STRUCT **firefly,
    EXPLOSION_STRUCT **explosion,
    SPRITES_STRUCT *sprites,
    AUDIO_STRUCT *audio,
    BUTTERFLY_STRUCT **butterfly,
    DIAMOND_STRUCT **diamond,
    BOULDER_STRUCT **boulder,
    ROCKFORD_STRUCT **rockford,
    AMOEBA_STRUCT **amoeba,
    DIRT_STRUCT **dirt,
    BRICK_WALL_STRUCT **brickWall,
    MAGIC_WALL_STRUCT **magicWall,
    STEEL_WALL_STRUCT **steelWall,
    EXIT_STRUCT **exit);

#endif