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

#pragma once

#include <SDL3/SDL.h>

#include <stdio.h>
#include <stdbool.h>

typedef struct {
  SDL_Window* handle;
  int width, height;
  bool initted;
} Window;

bool init_window(Window* win, const char* title, int width, int height);
void free_window(Window* win);

///////////////////////////////////////////////////////////////////////

typedef struct {
  SDL_Renderer* handle;
  bool initted;
} Renderer;

bool init_renderer(Renderer* ren, Window* win);
void free_renderer(Renderer* ren);


///////////////////////////////////////////////////////////////////////

typedef struct {
  Window* win;
  Renderer* ren;
  double delta_time;
  bool running;
  bool initted;
} Game;

bool init_game(Game* game, Window* win, Renderer* ren);
void free_game(Game* game);
void run_game(Game* game);

///////////////////////////////////////////////////////////////////////

typedef struct {
  float x, y;
} Vec2;

Vec2 construct_vec2(float x, float y);
Vec2 add_vec2(const Vec2 v1, const Vec2 v2);
Vec2 sub_vec2(const Vec2 v1, const Vec2 v2);
Vec2 mul_vec2(const Vec2 v1, const Vec2 v2);

///////////////////////////////////////////////////////////////////////

typedef struct {
  SDL_Texture* handle;
  SDL_FRect transform;
  bool initted;
} Texture;

bool init_texture(Texture* tex, Game* game, const char* path);
void free_texture(Texture* tex);


///////////////////////////////////////////////////////////////////////

typedef struct {
  Texture asset;
  bool initted;
} Paddle;

bool init_paddle(Paddle* paddle, Game* game, const char* asset_path, Vec2 position);
void free_paddle(Paddle* paddle);

typedef struct {
  Texture asset;
  bool initted;
} Ball;

bool init_ball(Ball* ball, Game* game, const char* asset_path, Vec2 position);
void free_ball(Ball* ball);
