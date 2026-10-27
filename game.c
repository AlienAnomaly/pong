#include "pong.h"

#define DEFAULT_PADDLE_SPEED 0.055f

static Paddle paddle1 = {0};
static Paddle paddle2 = {0};
static Ball ball = {0};

static void poll_events(Game* game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT: {
        game->running = false;
      } break;

      case SDL_EVENT_WINDOW_RESIZED: {
        game->win->width = event.window.data1;
        game->win->height = event.window.data2;
      } break;
    }
  }
}

static void update(Game* game) {
  const bool* keys = SDL_GetKeyboardState(NULL);

  if (paddle1.asset.transform.y > 0.0f && keys[SDL_SCANCODE_W]) {
    paddle1.asset.transform.y -= DEFAULT_PADDLE_SPEED;
  } else if (paddle1.asset.transform.y < 0) {
    paddle1.asset.transform.y = 0.0f;
  }

  if (paddle1.asset.transform.y < game->win->height - paddle1.asset.transform.h && keys[SDL_SCANCODE_S]) {
    paddle1.asset.transform.y += DEFAULT_PADDLE_SPEED;
  } else if (paddle1.asset.transform.y > game->win->height) {
    paddle1.asset.transform.y = game->win->height - paddle1.asset.transform.h;
  }
}

static void render(Game* game) {
  SDL_SetRenderDrawColor(game->ren->handle, 20, 20, 20, 255);
  SDL_RenderClear(game->ren->handle);

  // render the player paddles.
  SDL_RenderTexture(game->ren->handle, paddle1.asset.handle, NULL, &paddle1.asset.transform);
  SDL_RenderTexture(game->ren->handle, paddle1.asset.handle, NULL, &paddle2.asset.transform);
  SDL_RenderTexture(game->ren->handle, ball.asset.handle, NULL, &ball.asset.transform);

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

  init_paddle(&paddle1, game, "assets/test/paddle.png", (Vec2){0.0f, 0.0f});
  paddle1.asset.transform.x = 100.0f;
  paddle1.asset.transform.y = (win->height / 2) - (paddle1.asset.handle->h / 2);
  paddle1.asset.transform.w = paddle1.asset.handle->w;
  paddle1.asset.transform.h = paddle1.asset.handle->h;
  
  init_paddle(&paddle2, game, "assets/test/paddle.png", (Vec2){0.0f, 0.0f});
  paddle2.asset.transform.x = (game->win->width - 100.0f) - (paddle2.asset.transform.w / 2);
  paddle2.asset.transform.y = (win->height / 2) - (paddle2.asset.handle->h / 2);
  paddle2.asset.transform.w = paddle2.asset.handle->w;
  paddle2.asset.transform.h = paddle2.asset.handle->h;

  init_ball(&ball, game, "assets/test/ball.png", (Vec2){0.0f, 0.0f});
  ball.asset.transform.x = game->win->width / 2 - ball.asset.transform.w / 2;
  ball.asset.transform.y = game->win->height / 2 - ball.asset.transform.h / 2;
  
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
