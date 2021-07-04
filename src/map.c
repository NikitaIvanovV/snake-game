#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"
#include "utils.h"
#include "error.h"

#define MAX_CELLS (100*100)
#define INITIAL_LENGTH 3

static int cell_count;

Vector vectors_sum(Vector x, Vector y)
{
  Vector z = {x.x + y.x, x.y - y.y};
  return z;
}

bool vectors_eq(Vector x, Vector y)
{
  return ((x.x == y.x) && (x.y == y.y));
}

Snake create_snake(int x, int y, int max_parts) {
  Snake snake;

  snake.pos = (Coordinate){x, y};
  
  snake.length = 1;
  snake.pending_length = INITIAL_LENGTH - 1;

  snake.parts = calloc(max_parts, sizeof(SnakePart) * MAX_CELLS);

  SnakePart head = {snake.pos, HEAD};
  snake.parts[0] = head;

  return snake;
}

MapCellState get_cell_state(Map* map, Coordinate coord) {
  return map->cells[coord.x][coord.y];
}

void set_cell_state(Map* map, Coordinate coord, MapCellState state) {
  map->cells[coord.x][coord.y] = state;
}

MapCell get_cell(Map* map, Coordinate coord) {
  MapCell cell = {coord, get_cell_state(map, coord)};
  return cell;
}

bool is_snake_state(MapCellState state)
{
  return ((state == HEAD) || (state == BODY));
}

bool is_snake_in_cell(Map *map, Coordinate coord)
{
  MapCellState cell_state = get_cell_state(map, coord);
  return is_snake_state(cell_state);
}

SnakePart make_snake_part(Coordinate coord) {
  SnakePart part = {coord, BODY};
  return part;
}

MapCellsStates generate_map_cells(const int size_x, const int size_y) {
  MapCellsStates map_cells;
  calloc2(map_cells, size_x, size_y);
  
  for (size_t x = 0; x < size_x; x++) {
    for (size_t y = 0; y < size_y; y++) {
      MapCellState cell;
      map_cells[x][y] = cell;
    }
  }
  
  return map_cells;
}

void process_map_symbol(MapCell* cells, char character, int x, int y, int* snake_x, int* snake_y) {
  MapCell cell = {{x, y}, FREE};
  switch (character)
  {
  case '0':
    cell.state = WALL;
    cells[cell_count++] = cell;
    break;
  case 'a':
    cell.state = APPLE;
    cells[cell_count++] = cell;
    break;
  case 'x':
    if (*snake_x >= 0)
    {
      printf("Error: two snakes found\n");
      exit(1);
    }
    cell.state = HEAD;
    cells[cell_count++] = cell;
    *snake_x = x;
    *snake_y = y;
    break;
  case ' ':
    cells[cell_count++] = cell;
    break;
  default:
    printf("Error: unknown symbol: \"%c\"\n", character);
    exit(1);
  }
}

void read_map_file(Map* map, const char* filename) {
  FILE* file = fopen(filename, "r");

  if (file != NULL) {
    char character;
    int x = 0, y = 0, max_x = 0;
    
    MapCell* cells = calloc(MAX_CELLS, sizeof(MapCell));
    cell_count = 0;
    
    int snake_x = -1, snake_y;

    while (true) {
      character = fgetc(file);
    
      if (character == EOF)
        break;
      
      if (character == '\n') {
        max_x = max(max_x, x);
        x = 0;
        y++;
      } else {
        process_map_symbol(cells, character, x, y, &snake_x, &snake_y);
        x++;
      }
    }

    fclose(file);
    
    if (snake_x < 0) {
      printf("Error: no snakes found\n");
      exit(1);
    }
    
    int max_y = y;
    map->size.x = max_x;
    map->size.y = max_y;
    
    MapCellsStates map_cells = generate_map_cells(max_x, max_y);
    int state;
    Coordinate cell_coord;
    
    for (x = 0; x < max_x; x++) {
      for (y = 0; y < max_y; y++) {
        state = FREE;
        for (size_t i = 0; i < cell_count; i++) {
          cell_coord = cells[i].pos;
          if (cell_coord.x == x && cell_coord.y == y) {
            state = cells[i].state;
            break;
          }
        }
        map_cells[x][y] = state;
      }
    }

    map->cells = map_cells;
    map->snake = create_snake(snake_x, snake_y, max_x*max_y);

  } else {
    printf("File not found: \"%s\"\n", filename);
    exit(1);
  }
}

void redraw_snake(Map* map) {
  Snake* snake = &(map->snake);

  for (int x = 0; x < map->size.x; x++)
  {
    for (int y = 0; y < map->size.x; y++)
    {
      Coordinate pos = {x, y};
      MapCellState cell_state = get_cell_state(map, pos);

      if (! ((cell_state == FREE) || is_snake_state(cell_state)))
        continue;

      set_cell_state(map, pos, FREE);

      for (int snake_part_index = 0; snake_part_index < snake->length; snake_part_index++)
      {
        SnakePart part = snake->parts[snake_part_index];
        // printf("(%d, %d) %d\n", part.pos.x, part.pos.y, part.state);
        if (vectors_eq(part.pos, pos))
        {
          set_cell_state(map, pos, part.state);
          break;
        }
      }
      
    }
  }
  
}

void update_map(Map* map, Vector direction) {
  Snake *snake = &(map->snake);

  Coordinate new_pos = vectors_sum(snake->pos, direction);

  bool grow = snake->pending_length > 0;


  MapCell* cells_to_update = snake->parts;

  for (int i = snake->length-1; i > -1; i--)
  {
    Coordinate next_pos = (i == 0) ? new_pos : cells_to_update[i-1].pos;
    cells_to_update[i].pos = next_pos;
  }
  
  MapCellState tail_state;
  if (grow) {
    tail_state = BODY;
    snake->parts[snake->length] = make_snake_part(snake->pos);
  } else {
    tail_state = FREE;
  }

  // TODO: when everything will work, try this:
  // snake->pos = new_pos;
  snake->pos.x = new_pos.x;
  snake->pos.y = new_pos.y;

  if (grow)
  {
    snake->length++;
    snake->pending_length--;
  }

  redraw_snake(map);
}

MoveResult move(Map* map, int dx, int dy) {
  if (dx * dy != 0) {
    printf("Error: diagonal movement is not allowed\n");
    exit(1);
  }

  Vector direction = {dx, dy};
  
  Snake* snake = &(map->snake);

  Coordinate pos = snake->pos;
  Coordinate new_pos = vectors_sum(pos, direction);
  
  MapCellState new_cell = get_cell_state(map, new_pos);
  MoveResult result;
  switch (new_cell) {
    case FREE:
      result = MOVED;
      break;
    case APPLE:
      result = EATEN;
      break;
    case WALL:
    case HEAD:
    case BODY:
      result = DIED;
      break;
  }
  
  if (result == DIED) {
    return result;
  }
  
  printf("Length: %d; Pending length: %d\n", snake->length, snake->pending_length);
  printf("Snake pos: (%d, %d)\n", snake->pos.x, snake->pos.y);
  update_map(map, direction);
  
}

MoveResult move_up(Map* map) {
  return move(map, 0, 1);
}

MoveResult move_right(Map* map) {
  return move(map, 1, 0);
}

MoveResult move_down(Map* map) {
  return move(map, 0, -1);
}

MoveResult move_left(Map* map) {
  return move(map, -1, 0);
}
