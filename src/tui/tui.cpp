#include "tui.hpp"

#include "render_engine.hpp"
#include "window_manager.hpp"

TUI::TUI(WindowManager &wm) : wm_(wm) {
  raw();
  keypad(stdscr, TRUE);
  noecho();
}

void TUI::run() {
  editor_buffer_.emplace_back("");

  while (true) {
    RenderEngine::draw(wm_.getPane(EDITOR), editor_buffer_, scroll_offset_);
    int ch = wgetch(wm_.getPane(active_pane_));
    if (ch == 27) // ESC to quit
      break;

    handleInput(ch);
  }
}
