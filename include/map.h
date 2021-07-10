#ifndef NIKITA_SG_MAP_H
#define NIKITA_SG_MAP_H

#include "vector.h"

#define DEFAULT_MAP "../map.txt"

typedef enum
{
  IGNORED,
  MOVED,
  EATEN,
  DIED
} MoveResult;

typedef enum
{
  FREE,
  SNAKE,
  WALL,
  APPLE,
  HEAD,
  BODY1,
  BODY2,
} MapCellState;

typedef Vector Coordinate;

typedef struct
{
  Coordinate pos;
  MapCellState state;
} MapCell;

typedef MapCell SnakePart;

typedef struct
{
  Coordinate pos;
  Vector direction;
  SnakePart *parts;
  int length;
  int pending_length;
} Snake;

typedef MapCellState **MapCellsStates;

typedef struct
{
  const char *map_file;
  Vector size;
  int cells_length;
  MapCellsStates cells;
  Snake snake;
} Map;

bool is_snake_state(MapCellState state);

bool is_valid_snake_direction(Snake *snake, Vector direction);

Map init_map(const char *map_file);

void load_map(Map *);

void unload_map(Map *);

MoveResult move_snake(Map *, Vector direction);

void draw_map_t(Map *);

#endif
