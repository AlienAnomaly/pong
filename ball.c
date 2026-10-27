#include "pong.h"

bool init_ball(Ball* ball, Game* game, const char* asset_path, Vec2 position) {
  if (!ball || ball->initted) return false;
  if (init_texture(&ball->asset, game, asset_path)) return false;
  ball->initted = true;
  
  return true;
}

void free_ball(Ball* ball) {
  if (!ball || !ball->initted) return;
  free_texture(&ball->asset);
  ball->initted = false;
}
