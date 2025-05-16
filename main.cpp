#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "draw.hpp"
#include "snake.hpp"

int main()
{
  draw game(35, 15);
  snake snek(1);

  //main game loop
  while(true)
  {
    snek.render(game.world);
    game.render();
    sleep(0.75);
    system("clear");      //clear the terminal
  }

}
