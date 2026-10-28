/*
 * This is a simple pong clone, I am using to improve at data oriented C programming.
 * Copyright (C) 2026 Callum Uzzell
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "pong.h"

#define DEFAULT_PADDLE_SPEED 0.055f
#define DEFAULT_BALL_SPEED 0.055f
#define BALL_WIDTH 16
#define BALL_HEIGHT 16

static Paddle paddle1 = {0};
static Paddle paddle2 = {0};

static bool flip_h = false;
static bool flip_v = false;
static Ball ball = {0};

static bool check_collision(SDL_FRect r1, SDL_FRect r2) {
  return (r1.x < r2.x + r2.w &&
          r1.x + r1.w > r2.x &&
          r1.y < r2.y + r2.h &&
          r1.y + r1.h > r2.y);
}

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

  // Paddle 1 movement...
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

  // Paddle 2 movement...
  if (paddle2.asset.transform.y > 0.0f && keys[SDL_SCANCODE_UP]) {
    paddle2.asset.transform.y -= DEFAULT_PADDLE_SPEED;
  } else if (paddle2.asset.transform.y < 0) {
    paddle2.asset.transform.y = 0.0f;
  }

  if (paddle2.asset.transform.y < game->win->height - paddle2.asset.transform.h && keys[SDL_SCANCODE_DOWN]) {
    paddle2.asset.transform.y += DEFAULT_PADDLE_SPEED;
  } else if (paddle2.asset.transform.y > game->win->height) {
    paddle2.asset.transform.y = game->win->height - paddle2.asset.transform.h;
  }

  // 1. Left/Right Window Bounds (Score / Reset or simple bounce)
  if (ball.asset.transform.x > game->win->width - ball.asset.transform.w) {
    flip_h = true;
  } else if (ball.asset.transform.x < 0) {
    flip_h = false;
  }

  // 2. Top/Bottom Window Bounds (Bounce V)
  if (ball.asset.transform.y > game->win->height - ball.asset.transform.h) {
    flip_v = true;
  } else if (ball.asset.transform.y < 0) {
    flip_v = false;
  }

  // 3. Paddle 1 Collision
  if (check_collision(ball.asset.transform, paddle1.asset.transform)) {
    if (flip_h) {
      flip_h = false;
      ball.asset.transform.x = paddle1.asset.transform.x + paddle1.asset.transform.w;
    }
  }

  // 4. Paddle 2 Collision
  if (check_collision(ball.asset.transform, paddle2.asset.transform)) {
    if (!flip_h) {
      flip_h = true;
      ball.asset.transform.x = paddle2.asset.transform.x - ball.asset.transform.w;
    }
  }

  // Apply Ball Movement
  if (!flip_h) {
    ball.asset.transform.x += DEFAULT_BALL_SPEED;
  } else {
    ball.asset.transform.x -= DEFAULT_BALL_SPEED;
  }

  if (!flip_v) {
    ball.asset.transform.y += DEFAULT_BALL_SPEED;
  } else {
    ball.asset.transform.y -= DEFAULT_BALL_SPEED;
  }
}

static void render(Game* game) {
  SDL_SetRenderDrawColor(game->ren->handle, 20, 20, 20, 255);
  SDL_RenderClear(game->ren->handle);

  // render the player paddles and the ball.
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

  // INIT GAME OBJECTS
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
