#include "pong.h"

#include <SDL3_image/SDL_image.h>

bool init_texture(Texture* tex, Game* game, const char* path) {
  if (!tex || tex->initted) return false;

  tex->handle = IMG_LoadTexture(game->ren->handle, path);
  if (!tex->handle) {
    fprintf(stderr, "Failed to load texture. Error: %s\n", SDL_GetError());
    return false;
  }

  tex->transform.w = tex->handle->w;
  tex->transform.h = tex->handle->h;
  tex->initted = true;
}

void free_texture(Texture* tex) {
  if (!tex || !tex->initted) return;
}
