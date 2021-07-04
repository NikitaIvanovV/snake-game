#ifndef NIKITA_SG_MAP
#define NIKITA_SG_MAP

#define DEFAULT_MAP "../map.txt"

typedef enum {
  MOVED,
  EATEN,
  DIED
} MoveResult;

typedef enum {
  FREE,
  WALL,
  HEAD,
  BODY,
  APPLE
} MapCellState;

typedef struct {
  int x, y;
} Coordinate;

typedef Coordinate Vector;

typedef struct {
  Coordinate pos;
  MapCellState state;
} MapCell;

typedef MapCell SnakePart;

typedef struct {
  Coordinate pos;
  int length;
  int pending_length;
  SnakePart* parts;
} Snake;

typedef MapCellState** MapCellsStates;

typedef struct {
  int size_x;
  int size_y;
  MapCellsStates cells;
  Snake snake;
} Map;

void read_map_file(Map*, const char*);

MoveResult move_up(Map*);

MoveResult move_right(Map*);

MoveResult move_down(Map*);

MoveResult move_left(Map*);

#endif
