#include "tui.hpp"

#include "render_engine.hpp"
#include "window_manager.hpp"
#include <algorithm>
#include <ncurses.h>

TUI::TUI(WindowManager &wm) : wm_(wm) {
  raw();
  keypad(stdscr, TRUE);
  noecho();
}

void TUI::run() {
  editor_buffer_.emplace_back("");

  while (true) {
    WINDOW *active_window = wm_.getPane(active_pane_);
    RenderEngine::draw(wm_.getPane(EDITOR), editor_buffer_, scroll_offset_,
                       cursor_row_, cursor_col_);
    int ch = wgetch(active_window);
    if (ch == 27) // ESC to quit
      break;

    handleInput(ch);
  }
}

void TUI::switchPane(Pane new_pane) { active_pane_ = new_pane; }

int TUI::maxScroll() {
  int max_y, max_x;
  getmaxyx(wm_.getPane(active_pane_), max_y, max_x);
  int visible_rows = max_y - 2;
  return std::max(0, static_cast<int>(editor_buffer_.size()) - visible_rows);
}

void TUI::scrollUp() {
  scroll_offset_ = std::clamp(scroll_offset_ - 1, 0, maxScroll());
}

void TUI::scrollDown() {
  scroll_offset_ = std::clamp(scroll_offset_ + 1, 0, maxScroll());
}

TUI::~TUI() = default;

void TUI::handleInput(int ch) {
  // TODO: handle command logic

  // ctrl + A, similar to tmux. TODO: make the prefix customizable
  if (ch == 1) {
    awaiting_command_ = true;
    return;
  }

  if (!awaiting_command_) {
    if (active_pane_ != EDITOR)
      return;

    editor_buffer_[cursor_row_].insert(cursor_col_, 1, static_cast<char>(ch));
    cursor_col_++;
  }
}
