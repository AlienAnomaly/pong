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

int main() {
  Window win = {0};
  if (!init_window(&win, "Pong!", 800, 600)) {
    fprintf(stderr, "Failed to initialize window...\n");
    return 1;
  }

  Renderer ren = {0};
  if (!init_renderer(&ren, &win)) {
    fprintf(stderr, "Failed to initialize renderer...\n");
    return 1;
  }

  Game game = {0};
  if (!init_game(&game, &win, &ren)) {
    fprintf(stderr, "Failed to initialize game...\n");
    return 1;
  }

  run_game(&game);

  free_game(&game);
  free_renderer(&ren);
  free_window(&win);
  
  return 0;
}
