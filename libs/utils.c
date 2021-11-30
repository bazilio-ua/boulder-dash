#include "utils.h"

void initialize(
    bool isInitialized,
    const char *description)
{
  if (isInitialized)
    return;

  printf("couldn't initialize %s\n", description);
  exit(1);
}

void update_map_state(
    char map[MAP_HEIGHT][MAP_WIDTH],
    char updatedState,
    int i,
    int j)
{
  map[i][j] = updatedState;
}

bool is_space_empty(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_EMPTY);
}

bool is_space_dirt(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_DIRT);
}

bool is_space_diamond(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_DIAMOND);
}

bool is_space_boulder(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_BOULDER);
}

bool is_space_rockford(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_ROCKFORD);
}

bool is_space_brick_wall(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_BRICK_WALL);
}

bool is_space_steel_wall(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_STEEL_WALL);
}

bool is_space_firefly(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_FIREFLY);
}

bool is_space_butterfly(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_BUTTERFLY);
}

bool is_space_amoeba(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_AMOEBA);
}

bool is_space_magic_wall(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_MAGIC_WALL);
}

bool is_space_exit(
    char map[MAP_HEIGHT][MAP_WIDTH],
    int i,
    int j)
{
  return (map[i][j] == IS_EXIT);
}

int generate_random_number_between(
    int lower,
    int upper)
{
  return (rand() % (upper - lower + 1)) + lower;
}