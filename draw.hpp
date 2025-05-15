#pragma once

#include <vector>
#include <iostream>

class draw{
  private:
    int width;
    int height;
    std::vector<std::vector<int>> world;
  public:
    draw(int width, int height);

    void render();
    
};
