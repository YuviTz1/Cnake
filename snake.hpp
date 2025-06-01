#pragma once 
  
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <ncurses.h>
#include <random>
#include "draw.hpp"
#include "shared_mutex.hpp"

enum class directions {
  NONE,
  LEFT,
  UP,
  RIGHT,
  DOWN
};

class snake
{
  private:
    int length;
    bool mouth_anim_trigger = true;
    std::atomic<directions> move_dir{directions::NONE};
    std::thread input_thread;
    std::pair<int, int> food_position;
    bool grow_body = false;

  public:
    bool running = true;
    std::vector<std::pair<int,int>> body;
    
    snake(int length);
    ~snake();
    void render(std::vector<std::vector<char>> &world);
    void update(std::vector<std::vector<char>> &world);
    void read_input();
    void generate_food(const std::vector<std::vector<char>> &world);

    //implement destructor
};
