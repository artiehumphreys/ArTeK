#include "window_manager.hpp"

int main() {
  WindowManager wm;
  cbreak();
  int c;
  while ((c = wgetch(wm.getPane(EDITOR))) != ERR) {
    waddch(wm.getPane(EDITOR), c);
  }
  return 0;
}
