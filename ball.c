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
