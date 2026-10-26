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
