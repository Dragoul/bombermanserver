
#include <iostream>

typedef enum{
  PASS = 0;
  DOWN,
  UP,
  RIGHT,
  LEFT,
  PASS
};




Player::Player()
{
}

Player::~Player()
{
}

int move(Board board, Motion dir)
{

  switch(dir){
  case DOWN:
    if(board.free(x,y-1))
      y--;
    break;
  case UP:
  case RIGHT:
  case LEFT:
  case PASS:
  default:
  }
}
