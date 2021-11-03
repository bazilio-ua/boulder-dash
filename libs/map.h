#ifndef _MAPH_
#define _MAPH_

#include "utils.h"
#include "steel-wall.h"
#include "brick-wall.h"
#include "boulder.h"
#include "dirt.h"
#include "diamond.h"
#include "rockford.h"

void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], char *filePath);

void count_map_objects(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int *steelWallCount,
    int *brickWallCount,
    int *boulderCount,
    int *dirtCount, 
    int *diamondCount);

void init_map_objects(
    char map[MAP_HEIGHT][MAP_WIDTH],
    STEEL_WALL_STRUCT *steelWall,
    BRICK_WALL_STRUCT *brickWall,
    BOULDER_STRUCT *boulder,
    DIRT_STRUCT *dirt,
    DIAMOND_STRUCT *diamond,
    ROCKFORD_STRUCT *rockford,
    int *steelWallCount,
    int *brickWallCount,
    int *boulderCount,
    int *dirtCount,
    int *diamondCount);

#endif