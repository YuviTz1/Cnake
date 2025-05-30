#pragma once 
  
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <ncurses.h>
#include "draw.hpp"

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
  public:
    bool running = true;
    std::vector<std::pair<int,int>> body;
    
    snake(int length);
    ~snake();
    void render(std::vector<std::vector<char>> &world);
    void update();
    void read_input();

    //implement destructor
};
