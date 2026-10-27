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
