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
  Vector size;
  int cells_length;
  MapCellsStates cells;
  Snake snake;
} Map;

void read_map_file(Map*, const char*);

MoveResult move_up(Map*);

MoveResult move_right(Map*);

MoveResult move_down(Map*);

MoveResult move_left(Map*);

#endif
