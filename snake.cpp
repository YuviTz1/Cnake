#include "snake.hpp"

snake::snake(int length)
{
  this->length = length;
  this->body = std::vector<std::pair<int,int>>(1);
  body[0] = std::pair<int,int>(7,15);
}

void snake::render(std::vector<std::vector<char>> &world)
{
  // animate the snake mouth
  if(mouth_anim_trigger)
  {
    world[body[0].first][body[0].second] = 'o';
    mouth_anim_trigger=!mouth_anim_trigger;
  }
  else 
  { 
    world[body[0].first][body[0].second] = 'O';
    mouth_anim_trigger=!mouth_anim_trigger;
  }
  for(int i=1;i<body.size();i++)
  {
    world[body[i].first][body[i].second] = '*';
  }
}

void snake::update()
{

}

void snake::read_input()
{
  char user_input;
  while(true)
  {
    user_input = getch();
    switch(user_input)
    {
      case 'a':
        move_dir.store(directions::LEFT);
        break;
      case 'd':
        move_dir.store(directions::RIGHT);
        break;
      default:
        move_dir.store(directions::NONE);
        break;
    }
  }
}
