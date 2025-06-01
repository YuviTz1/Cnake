#pragma once

#include <vector>
#include <iostream>
#include <ncurses.h>
#include "shared_mutex.hpp"

class draw{
  private:
    int width;
    int height;

  public:
    std::vector<std::vector<char>> world;
    draw(int width, int height);

    void render();
    void clear_screen();
    
};
