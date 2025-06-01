#include "draw.hpp"

draw::draw(int width, int height)
{
  this->width = height;
  this->height = width;

  this->world = std::vector<std::vector<char>>(this->width, std::vector<char>(this->height));
  clear_screen();
}

void draw::render()
{
  std::lock_guard<std::mutex> lock(terminal_mutex); // Lock the mutex
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      //std::cout<<world[i][j];
      mvaddch(i,j,world[i][j]);
    }
    //std::cout<<std::endl;
  }
  refresh();
}

void draw::clear_screen()
{
  for(int i=0;i<width;i++)
  {
    for(int j=0;j<height;j++)
    {
      world[i][j]= ' ';
    }
  }
}
