#pragma once

#include <ncurses.h>

enum Pane { EDITOR, OUTPUT, LOG, PANE_COUNT };

class WindowManager {
public:
  WindowManager();
  ~WindowManager();

  WINDOW *getPane(Pane pane) const;
  void refreshAll();

private:
  int width, height;
  WINDOW *panes[PANE_COUNT];
};
