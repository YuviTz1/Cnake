#include "draw.hpp"

draw::draw(int width, int height)
{
  this->width = height;
  this->height = width;

  this->world = std::vector<std::vector<char>>(this->width, std::vector<char>(this->height));

  for(int i=0;i<this->width;i++)
  {
    for(int j=0;j<this->height;j++)
    {
      world[i][j] = ' ';
    }
  }
}

void draw::render()
{
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      std::cout<<world[i][j];
    }
    std::cout<<std::endl;
  }
}
