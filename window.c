#include "pong.h"

bool init_window(Window* win, const char* title, int width, int height) {
  if (!win || win->initted) return false; 

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Failed to init SDL. Error: %s\n", SDL_GetError());
    return false;  
  }

  win->handle = SDL_CreateWindow(title,
                                 width,
                                 height,
                                 SDL_WINDOW_RESIZABLE);

  if (!win->handle) {
    fprintf(stderr, "Failed to init SDL window. Error: %s\n", SDL_GetError());
    return false;
  }

  win->width = width;
  win->height = height;
  win->initted = true;

  return true;
}

void free_window(Window* win) {
  if (!win || !win->initted) return;
  if (win->handle) SDL_DestroyWindow(win->handle);
  win->handle = NULL;
  win->initted = false;
}
