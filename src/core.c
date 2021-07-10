#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "map.h"
#include "utils.h"
#include "render.h"

#define AUTOMOVE
#define TIMES_TO_MOVE_PER_SECOND (10)

typedef enum
{
    GAME_STATE_GAME,
    GAME_STATE_PAUSE,
} GameState;

typedef struct
{
    View view;
    Map map;
    Vector snake_direction;
    SDL_Event sdl_event;
    unsigned int frame_rate;
    unsigned int frame_in_second;
    bool running;
    GameState state;
} Game;

enum Event
{
    EVENT_NONE = 1,
    EVENT_SNAKE_DIRECTION_CHANGED,
    EVENT_ESCAPE,
    EVENT_RESTART,
    EVENT_EXIT
};

static Game game;

void init_game(Game *game, const char *map_file)
{
    game->map = init_map(map_file);

    game->snake_direction = (Vector){0, 0};

    game->frame_rate = 60;
    game->frame_in_second = 0;

    game->running = true;

    game->state = GAME_STATE_GAME;
}

Game create_game(const char *map_file)
{
    Game game;
    init_game(&game, map_file);

    game.view = init_view(&game.map);
    clear_screen(&game.view, 0, 0, 0);

    return game;
}

void clear_game(Game *game)
{
    clear_map(&game->map);
}

void close_game(Game *game)
{
    clear_game(game);
    quit_view(&game->view);
}

void restart_game(Game *game)
{
    const char* map_file = game->map.map_file;
    clear_game(game);
    init_game(game, map_file);
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
                event = EVENT_SNAKE_DIRECTION_CHANGED;
                break;
            case SDLK_DOWN:
                *new_direction = (Vector){0, -1};
                event = EVENT_SNAKE_DIRECTION_CHANGED;
                break;
            case SDLK_RIGHT:
                *new_direction = (Vector){1, 0};
                event = EVENT_SNAKE_DIRECTION_CHANGED;
                break;
            case SDLK_LEFT:
                *new_direction = (Vector){-1, 0};
                event = EVENT_SNAKE_DIRECTION_CHANGED;
                break;
            case SDLK_r:
                event = EVENT_RESTART;
                break;
            case SDLK_ESCAPE:
                event = EVENT_ESCAPE;
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
    Vector new_direction[1];
    enum Event event = handle_events(game, new_direction);

    if (event != EVENT_NONE)
    {
        if (event == EVENT_SNAKE_DIRECTION_CHANGED)
        {
            if (is_valid_snake_direction(&game->map.snake, *new_direction))
                game->snake_direction = *new_direction;
        }
        else if (event == EVENT_RESTART)
        {
            restart_game(game);
        }
        else if (event == EVENT_EXIT)
        {
            game->running = false;
        }
        else if (event == EVENT_ESCAPE)
        {
            game->state = (game->state == GAME_STATE_GAME) ? GAME_STATE_PAUSE : GAME_STATE_GAME;
        }
        else
        {
            printf("Error: invalid event type: %d\n", event);
            exit(1);
        }
    }

    if (game->state == GAME_STATE_GAME)
    {
        bool move =
        #ifdef AUTOMOVE
        (game->frame_in_second % (game->frame_rate / TIMES_TO_MOVE_PER_SECOND)) == 0;
        #else
        event == EVENT_SNAKE_DIRECTION_CHANGED;
        #endif
        if (move)
        {
            if (move_snake(&game->map, game->snake_direction) == DIED)
            {
                game->running = false;
                printf("You died.\nLength: %d\n", game->map.snake.length);
            }
        }
    }
    else if ((game->state == GAME_STATE_PAUSE))
    {
        
    }
    
}

void exit_game()
{
    close_game(&game);
}

void run_game(const char *map_file)
{
    atexit(exit_game);

    game = create_game(map_file);

    while (game.running)
    {
        update(&game);
        render_map(&game.view, &game.map);
        display(&game.view);

        SDL_Delay(1000.0 / game.frame_rate); // Absolutely improper way to make a game run at 60 FPS
        game.frame_in_second = (game.frame_in_second + 1) % game.frame_rate;
    }
}
