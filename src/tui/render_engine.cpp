#include "render_engine.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <string_view>
#include <vector>

void RenderEngine::draw(WINDOW *win, const std::vector<std::string> &lines,
                        int scroll_offset, int cursor_row, int cursor_col) {
  // approach: erase and re-draw every call
  // ncurses internally diffs old and new versions of window
  werase(win);
  box(win, 0, 0);

  int max_x, max_y;
  getmaxyx(win, max_y, max_x);

  int usable_width = max_x - 2;
  int visible_rows = max_y - 2;

  int screen_row = 1, screen_col = 1;

  for (int i = scroll_offset;
       i < static_cast<int>(lines.size()) && screen_row <= visible_rows; ++i) {
    std::string_view line = lines[i];
    if (line.empty()) {
      screen_row++;
      continue;
    }
    // process each string in buffer
    for (std::size_t offset = 0;
         offset < line.size() && screen_row <= visible_rows;
         offset += usable_width) {
      auto chunk = line.substr(offset, usable_width); // substr clamps bounds
      // TODO: line numbers
      if (mvwaddnstr(win, screen_row++, screen_col, chunk.data(),
                     chunk.size()) == ERR) {
        std::cerr << "An error occurred while displaying the text editor.\n";
        return;
      }
    }
  }

  wmove(win, cursor_row - scroll_offset + 1, cursor_col + 1);
  wrefresh(win);
}
