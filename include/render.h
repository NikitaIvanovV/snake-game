#ifndef NIKITA_SG_RENDER_H
#define NIKITA_SG_RENDER_H

#include <SDL2/SDL.h>

#include <map.h>

typedef struct {
  SDL_Surface* surface;
  SDL_Window* window;
  SDL_Renderer* renderer;
  int scale;
} View;

View init_view(Map* map);

void clear_screen(View* view, int r, int g, int b);

void display(View*);

void set_color(View* view, int r, int g, int b);

void draw_rect_c(View* view, int x, int y, int w, int h, int r, int g, int b);

void draw_rect(View* view, int x, int y, int w, int h);

void render_map(View* view, Map* map);

void quit_view(View*);

#endif
