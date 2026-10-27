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
