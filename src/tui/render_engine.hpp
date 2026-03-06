#pragma once

#include <ncurses.h>
#include <string>
#include <vector>

class RenderEngine {
public:
  static void draw(WINDOW *win, const std::vector<std::string> &lines,
                   int scroll_offset);
};
