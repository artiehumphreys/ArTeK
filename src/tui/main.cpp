#include "window_manager.hpp"

int main() {
  WindowManager wm;
  wgetch(wm.getPane(EDITOR));
  return 0;
}
