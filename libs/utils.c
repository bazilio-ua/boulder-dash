#include "utils.h"

void initialize(bool isInitialized, const char *description)
{
  if (isInitialized)
    return;

  printf("couldn't initialize %s\n", description);
  exit(1);
}

bool isCollision(int x1, int y1, int x2, int y2)
{
  return (x1 == x2 && y1 == y2);
}

void update_map_state(char map[MAP_HEIGHT][MAP_WIDTH], char updatedState, int i, int j)
{
  map[i][j] = updatedState;
}

bool isSpaceEmpty(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_EMPTY);
}

bool isSpaceDirt(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_DIRT);
}

bool isSpaceDiamond(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_DIAMOND);
}

bool isSpaceBoulder(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_BOULDER);
}

bool isSpaceRockford(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_ROCKFORD);
}

bool isSpaceBrickWall(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_BRICK_WALL);
}

bool isSpaceSteelWall(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_STEEL_WALL);
}

bool isSpaceFirefly(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_FIREFLY);
}

bool isSpaceButterfly(char map[MAP_HEIGHT][MAP_WIDTH], int i, int j)
{
  return (map[i][j] == IS_BUTTERFLY);
}