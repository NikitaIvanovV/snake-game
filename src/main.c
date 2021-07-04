#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "map.h"
#include "utils.h"
#include "render.h"

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

Map map;

void draw_map_t(Map* map) {
  for (size_t y = 0; y < map->size.y; y++) {
    for (size_t x = 0; x < map->size.x; x++) {
      printf("%d", map->cells[x][y]);
    }
    printf("\n");
  }
}

void restart_game(Map* map, const char* map_file) {
  free(map->cells);
  read_map_file(map, map_file);
}

int main(int argc, char const *argv[]) {
  const char* map_file = (argc == 2) ? argv[1] : DEFAULT_MAP;
  
  read_map_file(&map, map_file);
  
  View* view = init_view(&map);
  SDL_Renderer* renderer = view->renderer;
  SDL_Window* window = view->window;

  clear_screen(view, 0, 0, 0);

  bool run = true;
  SDL_Event e;
  MoveResult mr;
  
  int x=0, y=0;

  while (run) {
    while(SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        run = false;
      }

      if (e.type == SDL_KEYDOWN) {
        
        switch (e.key.keysym.sym) {
          case SDLK_UP:
            mr = move_up(&map);
            break;
          case SDLK_DOWN:
            mr = move_down(&map);
            break;
          case SDLK_RIGHT:
            mr = move_right(&map);
            break;
          case SDLK_LEFT:
            mr = move_left(&map);
            break;
          case SDLK_r:
            restart_game(&map, map_file);
            break;
        }

        draw_map_t(&map);
        if (mr == DIED)
        {
          run = false;
          printf("You died.\nLength: %d\n", map.snake.length);
        }
      }
    }
    
    render_map(view);
    draw(view);
    SDL_Delay(1000.0 / 60);
  }
  
  quit_view(view);
}
