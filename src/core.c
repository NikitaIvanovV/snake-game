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
    SDL_Event sdl_event;
    bool running;
} Game;

enum Event
{
    EVENT_NONE = 1,
    EVENT_SNAKE_MOVED,
    EVENT_RESTART,
    EVENT_EXIT
};

void restart_game(Game *game)
{
    unload_map(&game->map);
    load_map(&game->map);
}

enum Event handle_events(Game *game, Vector *new_direction)
{
    Map *map = &game->map;
    enum Event event = EVENT_NONE;

    while (SDL_PollEvent(&game->sdl_event) != 0)
    {
        if (game->sdl_event.type == SDL_QUIT)
            event = EVENT_EXIT;

        else if (game->sdl_event.type == SDL_KEYDOWN)
        {
            switch (game->sdl_event.key.keysym.sym)
            {
            case SDLK_UP:
                *new_direction = (Vector){0, 1};
                event = EVENT_SNAKE_MOVED;
                break;
            case SDLK_DOWN:
                *new_direction = (Vector){0, -1};
                event = EVENT_SNAKE_MOVED;
                break;
            case SDLK_RIGHT:
                *new_direction = (Vector){1, 0};
                event = EVENT_SNAKE_MOVED;
                break;
            case SDLK_LEFT:
                *new_direction = (Vector){-1, 0};
                event = EVENT_SNAKE_MOVED;
                break;
            case SDLK_r:
                event = EVENT_RESTART;
                break;
            }    
        }
        // Prevent event from overwriting if there's another event in the poll
        if (event == EVENT_EXIT)
            break;
    }

    return event;
}

MoveResult move(Game *game, Vector dir)
{
    move_snake(&game->map, dir);
}

void update(Game *game)
{
    static Vector new_direction;

    Vector *dir;
    enum Event event = handle_events(game, dir);

    if (event == EVENT_NONE)
        return;

    if (event == EVENT_SNAKE_MOVED)
    {
        MoveResult mr = move(game, *dir);

        if (mr == DIED)
        {
            game->running = false;
            printf("You died.\nLength: %d\n", game->map.snake.length);
        }
    }
    else if (event == EVENT_RESTART)
    {
        restart_game(game);
    }
    else if (event == EVENT_EXIT)
    {
        game->running = false;
    }
    else
    {
        printf("Error: invalid event type: %d\n", event);
        exit(1);
    }
}

Game init_game(const char *map_file)
{
    Game game;

    game.map = init_map(map_file);
    load_map(&game.map);

    game.view = init_view(&game.map);
    clear_screen(&game.view, 0, 0, 0);

    game.running = true;

    return game;
}

void clean_game(Game *game)
{
    quit_view(&game->view);
}

void run_game(const char *map_file)
{
    Game game = init_game(map_file);

    unsigned int frame_in_second = 0;
    unsigned int frame_rate = 60;

    while (game.running)
    {
        update(&game);
        render_map(&game.view, &game.map);
        display(&game.view);

        SDL_Delay(1000.0 / frame_rate); // Absolutely improper way to make a game run at 60 FPS
        frame_in_second = (frame_in_second + 1) % frame_rate;
    }

    clean_game(&game);
}
