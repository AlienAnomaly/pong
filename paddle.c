#include "pong.h"

#include <stdio.h>
#include <stdbool.h>

bool init_paddle(Paddle* paddle, Game* game, const char* asset_path, Vec2 position) {
  if (!paddle || paddle->initted) return false;
  if (!init_texture(&paddle->asset, game, asset_path)) return false;
  paddle->initted = true;

  return true;
}

void free_paddle(Paddle* paddle) {
  if (!paddle || !paddle->initted) return;
  free_texture(&paddle->asset);
  paddle->initted = false;  
}
