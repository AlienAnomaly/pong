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
