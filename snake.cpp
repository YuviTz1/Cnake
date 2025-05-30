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
  if(move_dir.load() == directions::LEFT)
  {
    body[0].second -=1;
  }
  else if(move_dir.load() == directions::RIGHT)
  {
    body[0].second +=1;
  }
  else if(move_dir.load() == directions::UP)
  {
    body[0].first -=1;
  }
  else if(move_dir.load() == directions::DOWN)
  {
    body[0].first +=1;
  }
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
        if(move_dir.load() != directions::RIGHT) // prevent reversing direction
          move_dir.store(directions::LEFT);
        break;
      case 'd':
        if(move_dir.load() != directions::LEFT) // prevent reversing direction
          move_dir.store(directions::RIGHT);
        break;
      case 'w':
        if(move_dir.load() != directions::DOWN) // prevent reversing direction
          move_dir.store(directions::UP);
        break;
      case 's':
        if(move_dir.load() != directions::UP) // prevent reversing direction
          move_dir.store(directions::DOWN);
        break;
      case 'q':
        running = false;
        break;
      default:
        move_dir.store(move_dir.load());  // keep the current direction
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
