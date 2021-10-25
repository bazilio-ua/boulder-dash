#include "utils.h"

void initialize(bool isInitialized, const char *description)
{
  if (isInitialized)
    return;

  printf("couldn't initialize %s\n", description);
  exit(1);
}
