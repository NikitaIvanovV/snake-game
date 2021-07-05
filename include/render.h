#ifndef NIKITA_SG_RENDER
#define NIKITA_SG_RENDER

#include <SDL2/SDL.h>

#include <map.h>

#define SDL_SCREEN_WIDTH 500
#define SDL_SCREEN_HEIGHT 500

typedef struct {
  Map* map;
  SDL_Surface* surface;
  SDL_Window* window;
  SDL_Renderer* renderer;
} View;

View* init_view();

void clear_screen(View* view, int r, int g, int b);

void draw(View*);

void set_color(View* view, int r, int g, int b);

void draw_rect_c(View* view, int x, int y, int w, int h, int r, int g, int b);

void draw_rect(View* view, int x, int y, int w, int h);

void render_map(View* view);

void quit_view(View*);

#endif
