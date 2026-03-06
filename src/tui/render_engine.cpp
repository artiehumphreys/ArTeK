#include "render_engine.hpp"

#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

void RenderEngine::draw(WINDOW *win, const std::vector<std::string> &lines,
                        int scroll_offset) {
  // approach: erase and re-draw every call
  // TODO: track dirty lines when there isn't a scroll so all lines aren't
  // redrawn when they don't need to be
  werase(win);
  box(win, 0, 0);

  int max_x, max_y;
  getmaxyx(win, max_y, max_x);

  int visible_rows = max_y - 2;

  for (int i = 0;
       i < visible_rows && scroll_offset + i < static_cast<int>(lines.size());
       ++i) {
    // maybe use mvwaddchnstr later on for syntax highlighting
    mvwaddnstr(win, i + 1, 1, lines[scroll_offset + i].c_str(), max_x - 2);
  }

  wrefresh(win);
}
