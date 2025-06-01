#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>
#include "draw.hpp" 
#include "snake.hpp"
#include "shared_mutex.hpp"

std::mutex terminal_mutex;

int main()
{
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  draw game(35, 15);
  snake snek(1);

  //main game loop
  while(snek.running)
  {
    snek.render(game.world);
    game.render();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    //system("clear");      //clear the terminal
    game.clear_screen();
    snek.update(game.world);
  }
  endwin();
}
