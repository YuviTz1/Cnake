#include <iostream>
#include "draw.hpp"
#include "snake.hpp"

int main()
{
  draw game(35, 15);
  snake snek(1);

  snek.render(game.world);
  game.render();

}
