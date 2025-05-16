#pragma once 
  
#include <iostream>
#include <vector>
#include "draw.hpp"

class snake
{
  private:
    int length;
  public:
    std::vector<std::pair<int,int>> body;
    
    snake(int length);
    void render(std::vector<std::vector<char>> &world);
    void update();
};
