#pragma once

#include "window_manager.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

class TUI {
public:
  explicit TUI(WindowManager &wm);
  ~TUI();

  void run();

  void switchPane(Pane new_pane);

  void scrollUp();
  void scrollDown();

private:
  WindowManager &wm_;
  std::vector<std::string> editor_buffer_, output_buffer_;
  int cursor_row_ = 0;
  int cursor_col_ = 0;
  int scroll_offset_ = 0;
  Pane active_pane_ = EDITOR;

  void handleInput(int ch);
};
