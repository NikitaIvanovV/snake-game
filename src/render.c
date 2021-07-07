#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "render.h"
#include "map.h"

#define SDL_SCREEN_WIDTH 500
#define SDL_SCREEN_HEIGHT 500
#define SDL_SDL_WINDOWPOS_X SDL_WINDOWPOS_UNDEFINED
#define SDL_SDL_WINDOWPOS_Y SDL_WINDOWPOS_UNDEFINED

View init_view(Map *map)
{
  SDL_DisplayMode displayMode;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("Error while initializing SDL\n");
    exit(1);
  }

  SDL_Surface *screen_surface = NULL;
  SDL_Window *window = NULL;

  window = SDL_CreateWindow("Snake", SDL_SDL_WINDOWPOS_X, SDL_SDL_WINDOWPOS_Y, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if (window == NULL)
  {
    printf("Error while creating a window\n");
    exit(1);
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  View view;
  view.surface = screen_surface;
  view.window = window;
  view.renderer = renderer;
  view.scale = (map->size.x < map->size.y) ? SDL_SCREEN_HEIGHT / map->size.y : SDL_SCREEN_WIDTH / map->size.x;

  return view;
}

void clear_screen(View *view, int r, int g, int b)
{
  SDL_SetRenderDrawColor(view->renderer, r, g, b, 255);
  SDL_RenderClear(view->renderer);
}

void display(View *view)
{
  SDL_RenderPresent(view->renderer);
}

void set_color(View *view, int r, int g, int b)
{
  SDL_SetRenderDrawColor(view->renderer, r, g, b, 255);
}

void draw_rect_c(View *view, int x, int y, int w, int h, int r, int g, int b)
{
  set_color(view, r, g, b);
  draw_rect(view, x, y, w, h);
}

void draw_rect(View *view, int x, int y, int w, int h)
{
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;

  SDL_RenderFillRect(view->renderer, &r);
}

void render_map(View *view, Map *map)
{
  for (int y = 0; y < map->size.y; y++)
  {
    for (int x = 0; x < map->size.x; x++)
    {
      switch (map->cells[x][y])
      {
      case FREE:
        set_color(view, 0, 0, 0);
        break;
      case WALL:
        set_color(view, 255, 255, 255);
        break;
      case HEAD:
        set_color(view, 255, 65, 0);
        break;
      case BODY:
        set_color(view, 255, 200, 00);
        break;
      case BODY2:
        set_color(view, 255, 160, 00);
        break;
      case APPLE:
        set_color(view, 255, 0, 0);
        break;
      default:
        printf("Error: uknown cell state: %d\n", map->cells[x][y]);
        exit(1);
      }

      draw_rect(view, x * view->scale, y * view->scale, view->scale, view->scale);
    }
  }
}

void quit_view(View *view)
{
  SDL_DestroyWindow(view->window);
  SDL_Quit();
}
