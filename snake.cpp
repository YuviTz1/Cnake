#include "snake.hpp"

snake::snake(int length)
{
  this->length = length;
  this->body = std::vector<std::pair<int,int>>(1);
  body[0] = std::pair<int,int>(7,15);
  input_thread = std::thread(&snake::read_input, this);
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
  while(running)
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
      case 'q':
        running = false;
        break;
      default:
        move_dir.store(directions::NONE);
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

snake::~snake()
{
  if(input_thread.joinable())
    input_thread.join();
}
