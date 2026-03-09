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
  if (awaiting_command_) {
    switch (ch) {
      // TODO: better navigation
    case 'l':
      switchPane(OUTPUT);
      return;
    case 'h':
      switchPane(EDITOR);
      return;
    case 'j':
      switchPane(LOG);
      return;
    }
    return;
  }

  if (ch == 1) {
    // ctrl + A, similar to tmux. TODO: make the prefix customizable
    awaiting_command_ = true;
    return;
  }

  if (active_pane_ != EDITOR)
    return;

  switch (ch) {
  case '\n':
  case KEY_ENTER:
    // split current line at cursor, insert new line
    editor_buffer_.insert(editor_buffer_.begin() + cursor_row_ + 1,
                          editor_buffer_[cursor_row_].substr(cursor_col_));
    editor_buffer_[cursor_row_].erase(cursor_col_);
    cursor_row_++;
    cursor_col_ = 0;
    return;

  case KEY_BACKSPACE:
  case 127:
    if (cursor_col_ > 0) {
      editor_buffer_[cursor_row_].erase(cursor_col_ - 1, 1);
      cursor_col_--;
    } else if (cursor_row_ > 0) {
      cursor_col_ = editor_buffer_[cursor_row_ - 1].size();
      editor_buffer_[cursor_row_ - 1] += editor_buffer_[cursor_row_];
      editor_buffer_.erase(editor_buffer_.begin() + cursor_row_);
      cursor_row_--;
    }
    return;
  case KEY_STAB:
  case 9:
    // TODO: customizable tab size
    int tab_size = 4;
    editor_buffer_[cursor_row_].insert(cursor_col_, tab_size, ' ');
    cursor_col_ += tab_size;
    return;
  }

  editor_buffer_[cursor_row_].insert(cursor_col_, 1, static_cast<char>(ch));
  cursor_col_++;
}
