#include <stdio.h>
#include <time.h>
#include "core.h"

#ifdef __unix__

#define OS_Windows false
#include <unistd.h>
// #include <string.h>

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows true
#include <windows.h>
// #include <tchar.h>
// #define DIV 1048576
// #define WIDTH 7

#endif

int main(int argc, char const *argv[])
{
  srand(time(NULL));
  const char *map_file = (argc == 2) ? argv[1] : NULL;
  run_game(map_file);
}
