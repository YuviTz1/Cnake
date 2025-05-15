#include "draw.hpp"

draw::draw(int width, int height)
{
  this->width = width;
  this->height = height;

  this->world = std::vector<std::vector<int>>(width, std::vector<int>(height));
}

void draw::render()
{
  for(int i=0;i<width;i++)
  {
    for(int i=0;i<height;i++)
    {
      std::cout<<"*";
    }
    std::cout<<std::endl;
  }
}
