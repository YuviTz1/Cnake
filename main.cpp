#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>
#include "draw.hpp" 
#include "snake.hpp"

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
    sleep(0.7);
    //system("clear");      //clear the terminal
    game.clear_screen();
    snek.update();
  }
  endwin();
}
