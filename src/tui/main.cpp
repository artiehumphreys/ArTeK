#include "tui.hpp"
#include "window_manager.hpp"

int main() {
  WindowManager wm;
  TUI tui(wm);
  tui.run();
  return 0;
}
