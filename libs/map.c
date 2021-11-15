#include "map.h"

void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], char *filePath)
{
  FILE *file;
  char c;
  int i = 0;
  int j = 0;

  file = fopen(filePath, "r");
  initialize(file, "mapa");

  c = fgetc(file);
  while (c != EOF)
  {
    if (c != 32 && c != '\n')
    {
      map[i][j] = c;
      j++;

      if (j >= MAP_WIDTH)
      {
        j = 0;
        i++;
      }
    }

    c = fgetc(file);
  }

  fclose(file);
}

void count_map_objects(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int *steelWallCount,
    int *brickWallCount,
    int *boulderCount,
    int *dirtCount,
    int *diamondCount,
    int *fireflyCount,
    int *butterflyCount,
    int *amoebaCount,
    int *magicWallCount)
{
  for (int i = 0; i < MAP_HEIGHT; i++)
    for (int j = 0; j < MAP_WIDTH; j++)
      switch (map[i][j])
      {
      case IS_STEEL_WALL:
        (*steelWallCount)++;
        break;
      case IS_BRICK_WALL:
        (*brickWallCount)++;
        break;
      case IS_BOULDER:
        (*boulderCount)++;
        break;
      case IS_DIRT:
        (*dirtCount)++;
        break;
      case IS_DIAMOND:
        (*diamondCount)++;
        break;
      case IS_FIREFLY:
        (*fireflyCount)++;
        break;
      case IS_BUTTERFLY:
        (*butterflyCount)++;
        break;
      case IS_AMOEBA:
        (*amoebaCount)++;
        break;
      case IS_MAGIC_WALL:
        (*magicWallCount)++;
        break;
      default:
        break;
      }
}

void init_map_objects(
    char map[MAP_HEIGHT][MAP_WIDTH],
    STEEL_WALL_STRUCT *steelWall,
    BRICK_WALL_STRUCT *brickWall,
    BOULDER_STRUCT *boulder,
    DIRT_STRUCT *dirt,
    DIAMOND_STRUCT *diamond,
    ROCKFORD_STRUCT *rockford,
    FIREFLY_STRUCT *firefly,
    BUTTERFLY_STRUCT *butterfly,
    AMOEBA_STRUCT *amoeba,
    MAGIC_WALL_STRUCT *magicWall,
    int *steelWallCount,
    int *brickWallCount,
    int *boulderCount,
    int *dirtCount,
    int *diamondCount,
    int *fireflyCount,
    int *butterflyCount,
    int *amoebaCount,
    int *magicWallCount,
    int count)
{
  for (int i = 0; i < MAP_HEIGHT; i++)
    for (int j = 0; j < MAP_WIDTH; j++)
      switch (map[i][j])
      {
      case IS_STEEL_WALL:
        steel_wall_init(&steelWall[*steelWallCount], j * BLOCK_SIZE, i * BLOCK_SIZE);
        (*steelWallCount)++;
        break;
      case IS_BRICK_WALL:
        brick_wall_init(&brickWall[*brickWallCount], j * BLOCK_SIZE, i * BLOCK_SIZE);
        (*brickWallCount)++;
        break;
      case IS_BOULDER:
        boulder_init(&boulder[*boulderCount], j * BLOCK_SIZE, i * BLOCK_SIZE);
        (*boulderCount)++;
        break;
      case IS_DIRT:
        dirt_init(&dirt[*dirtCount], j * BLOCK_SIZE, i * BLOCK_SIZE);
        (*dirtCount)++;
        break;
      case IS_DIAMOND:
        diamond_init(&diamond[*diamondCount], j * BLOCK_SIZE, i * BLOCK_SIZE);
        (*diamondCount)++;
        break;
      case IS_ROCKFORD:
        rockford_init(rockford, j * BLOCK_SIZE, i * BLOCK_SIZE);
        break;
      case IS_FIREFLY:
        firefly_init(&firefly[*fireflyCount], j * BLOCK_SIZE, i * BLOCK_SIZE);
        (*fireflyCount)++;
        break;
      case IS_BUTTERFLY:
        butterfly_init(&butterfly[*butterflyCount], j * BLOCK_SIZE, i * BLOCK_SIZE);
        (*butterflyCount)++;
        break;
      case IS_AMOEBA:
        amoeba_init(&amoeba[*amoebaCount], j * BLOCK_SIZE, i * BLOCK_SIZE, count);
        (*amoebaCount)++;
        break;
      case IS_MAGIC_WALL:
        magic_wall_init(&magicWall[*magicWallCount], j * BLOCK_SIZE, i * BLOCK_SIZE);
        (*magicWallCount)++;
        break;
      default:
        break;
      }
}