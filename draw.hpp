#pragma once

#include <vector>
#include <iostream>

class draw{
  private:
    int width;
    int height;

  public:
    std::vector<std::vector<char>> world;
    draw(int width, int height);

    void render();
    
};
