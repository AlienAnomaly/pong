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
