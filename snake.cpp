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

  world[food_position.first][food_position.second] = '$';
}

void snake::update(std::vector<std::vector<char>> &world)
{
  if(grow_body == true)
  {
    // Add a new segment to the snake's body
    body.push_back(body.back());
    grow_body = false; // Reset the grow flag
  }

  // Move the body segments to follow the head
  for (int i = body.size() - 1; i > 0; i--)
  {
    body[i] = body[i - 1];
  }

  //move the head
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

  //check for collision with self
  for (int i = 1; i < body.size(); ++i)
  {
    if (body[0] == body[i])
    {
      running = false; // End the game
      break;
    }
  }

  //wrap around the screen
  if (body[0].first < 0)
  {
    body[0].first = world.size() - 1;
  }
  else if (body[0].first >= world.size())
  {
    body[0].first = 0;
  }

  if (body[0].second < 0)
  {
    body[0].second = world[0].size() - 1;
  }
  else if (body[0].second >= world[0].size())
  {
    body[0].second = 0;
  }

  //check for collision with food
  if (body[0] == food_position)
  {
    grow_body = true;
    generate_food(world); // Generate new food position
  }
}

void snake::read_input()
{
  char user_input;
  while(running)
  {
    {
      std::lock_guard<std::mutex> lock(terminal_mutex); // Lock the mutex
      user_input = getch();
    }
    if (user_input != ERR)
    {
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
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void snake::generate_food(const std::vector<std::vector<char>> &world)
{
  static std::random_device rd; // Seed generator
  static std::mt19937 gen(rd()); // Mersenne Twister engine
  int rows = world.size();
  int cols = world[0].size();
  std::uniform_int_distribution<> row_dist(0, rows - 1);
  std::uniform_int_distribution<> col_dist(0, cols - 1);

  while (true)
  {
    int x = row_dist(gen);
    int y = col_dist(gen);

    // Ensure food is not on the snake's body
    bool is_on_snake = false;
    for (const auto &segment : body)
    {
      if (segment.first == x && segment.second == y)
      {
        is_on_snake = true;
        break;
      }
    }

    if (!is_on_snake)
    {
      food_position = {x, y};
      break;
    }
  }
}

snake::~snake()
{
  if(input_thread.joinable())
    input_thread.join();
}
