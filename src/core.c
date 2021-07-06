#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "map.h"
#include "utils.h"
#include "render.h"

typedef struct
{
    View view;
    Map map;
    bool running;
} Game;

void restart_game(Game *game)
{
    unload_map(&game->map);
    load_map(&game->map);
}

MoveResult register_keys(Game *game, SDL_Event *e)
{
    MoveResult mr;
    Map *map = &game->map;

    while (SDL_PollEvent(e) != 0)
    {
        if (e->type == SDL_QUIT)
        {
            game->running = false;
        }

        if (e->type == SDL_KEYDOWN)
        {

            switch (e->key.keysym.sym)
            {
            case SDLK_UP:
                mr = move_up(map);
                break;
            case SDLK_DOWN:
                mr = move_down(map);
                break;
            case SDLK_RIGHT:
                mr = move_right(map);
                break;
            case SDLK_LEFT:
                mr = move_left(map);
                break;
            case SDLK_r:
                restart_game(game);
                break;
            }

            if (mr == DIED)
            {
                game->running = false;
                printf("You died.\nLength: %d\n", map->snake.length);
            }
        }
    }
}

Game init_game(const char *map_file)
{
    Game game;

    game.map = init_map(map_file);
    load_map(&game.map);

    game.view = init_view(game.map);
    clear_screen(&game.view, 0, 0, 0);

    game.running = true;

    return game;
}

void run_game(const char *map_file)
{
    Game game = init_game(map_file);
    SDL_Event e;
    MoveResult mr;

    while (game.running)
    {
        mr = register_keys(&game, &e);
        render_map(&game.view, &game.map);
        draw(&game.view);
        SDL_Delay(1000.0 / 60);
    }

    quit_view(&game.view);
}
