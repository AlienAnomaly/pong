#include "pong.h"

static void poll_events(Game* game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT: {
        game->running = false;
      } break;
    }
  }
}

static void update(Game* game) {
  
}

static void render(Game* game) {
  SDL_SetRenderDrawColor(game->ren->handle, 20, 20, 20, 255);
  SDL_RenderClear(game->ren->handle);
  SDL_RenderPresent(game->ren->handle);
}

bool init_game(Game* game, Window* win, Renderer* ren) {
  if (!game || !win || !ren || game->initted) return false;

  game->win = win;
  game->ren = ren;
  game->delta_time = 0.0;
  game->running = true;
  game->initted = true;

  if (!game->win || !game->ren) return false;

  return true;
}

void free_game(Game* game) {
  if (!game || !game->initted) return;
  game->ren = NULL;
  game->win = NULL;
  game->running = false;
  game->initted = false;
}

void run_game(Game* game) {
  while (game->running) {
    poll_events(game);
    update(game);
    render(game);
  }
}
