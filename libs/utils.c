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