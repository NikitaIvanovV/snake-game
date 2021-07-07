#ifndef NIKITA_SG_CORE
#define NIKITA_SG_CORE

#include <stdbool.h>
#include "render.h"
#include "map.h"

#define WALL_MODE false

int run_game(const char *map_file);

void draw_map_t(Map* map);

#endif
