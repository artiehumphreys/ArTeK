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

  int usable_width = max_x - 6;
  int visible_rows = max_y - 2;

  int screen_row = 1, screen_col = 4;
  int extra_rows = 0;

  for (int i = scroll_offset;
       i < static_cast<int>(lines.size()) && screen_row <= visible_rows; ++i) {
    bool is_first_chunk = true;
    std::string_view line = lines[i];

    if (line.empty()) {
      mvwprintw(win, screen_row, 1, "%-3d ", i + 1);
      screen_row++;
      continue;
    }

    if (i < cursor_row) {
      int len = line.size();
      extra_rows += len / usable_width;
    }

    // process each string in buffer
    for (std::size_t offset = 0;
         offset < line.size() && screen_row <= visible_rows;
         offset += usable_width) {
      if (is_first_chunk) {
        mvwprintw(win, screen_row, 1, "%-3d ", i + 1);
        is_first_chunk = false;
      } else {
        mvwprintw(win, screen_row, 1, "    ");
      }

      auto chunk = line.substr(offset, usable_width); // substr clamps bounds
      if (mvwaddnstr(win, screen_row++, screen_col, chunk.data(),
                     chunk.size()) == ERR) {
        // TODO: log in console window
        std::cerr << "An error occurred while displaying the text editor.\n";
        return;
      }
    }
  }

  wmove(win, cursor_row - scroll_offset + 1 + extra_rows + cursor_col / usable_width,
        cursor_col % usable_width + screen_col);
  wrefresh(win);
}
