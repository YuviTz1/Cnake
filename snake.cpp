#include "snake.hpp"

snake::snake(int length)
{
  this->length = length;
  this->body = std::vector<std::pair<int,int>>(1);
  body[0] = std::pair<int,int>(7,15);
}

void snake::render(std::vector<std::vector<char>> &world)
{
  world[body[0].first][body[0].second] = 'O';
  for(int i=1;i<body.size();i++)
  {
    world[body[i].first][body[i].second] = '*';
  }
}

void update()
{

}
