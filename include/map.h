#ifndef NIKITA_SG_MAP
#define NIKITA_SG_MAP

#include "vector.h"

#define DEFAULT_MAP "../map.txt"

typedef enum {
  IGNORED,
  MOVED,
  EATEN,
  DIED
} MoveResult;

typedef enum {
  FREE,
  WALL,
  HEAD,
  BODY,
  BODY2,
  APPLE
} MapCellState;

typedef Vector Coordinate;

typedef struct {
  Coordinate pos;
  MapCellState state;
} MapCell;

typedef MapCell SnakePart;

typedef struct {
  Coordinate pos;
  Vector direction;
  SnakePart* parts;
  int length;
  int pending_length;
} Snake;

typedef MapCellState** MapCellsStates;

typedef struct {
  const char *map_file;
  Vector size;
  int cells_length;
  MapCellsStates cells;
  Snake snake;
} Map;

bool is_valid_snake_direction(Snake *snake, Vector direction);

Map init_map(const char *map_file);

void load_map(Map*);

void unload_map(Map *);

MoveResult move_up(Map*);

MoveResult move_right(Map*);

MoveResult move_down(Map*);

MoveResult move_left(Map*);

MoveResult move_snake(Map *, Vector direction);

void draw_map_t(Map*);

#endif
