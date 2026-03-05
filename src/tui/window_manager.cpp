#include "window_manager.hpp"

WindowManager::WindowManager() {
  initscr();
  getmaxyx(stdscr, height, width);

  int log_height = height / 5;
  int top_height = height - log_height;
  int editor_width = width * 3 / 5;
  int output_width = width - editor_width;

  panes[EDITOR] = newwin(top_height, editor_width, 0, 0);
  panes[OUTPUT] = newwin(top_height, output_width, 0, editor_width);
  panes[LOG] = newwin(log_height, width, top_height, 0);

  for (auto &pane : panes) {
    box(pane, 0, 0);
    wrefresh(pane);
  }
}

WindowManager::~WindowManager() {
  for (auto &pane : panes) {
    delwin(pane);
  }
  endwin();
}

WINDOW *WindowManager::getPane(Pane pane) const { return panes[pane]; }

void WindowManager::refreshAll() {
  for (auto &pane : panes) {
    wrefresh(pane);
  }
}
