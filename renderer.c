#include "pong.h"

bool init_renderer(Renderer* ren, Window* win) {
  if (!ren || !win || ren->initted) return false;

  ren->handle = SDL_CreateRenderer(win->handle, NULL);
  if (!ren->handle) {
    fprintf(stderr, "Failed to init SDL renderer. Error: %s\n", SDL_GetError());
    return false;
  }

  ren->initted = true;

  return true;
}

void free_renderer(Renderer* ren) {
  if (!ren || !ren->initted) return;
  if (ren->handle) SDL_DestroyRenderer(ren->handle);
  ren->handle = NULL;
}
