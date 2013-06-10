


#include "player.h"

#include "../include/log.h"

Player::Player(int x_, int y_) : x(x_), y(y_)
{
}

Player::~Player()
{
}

int Player::move(Board board, PlayerMotionType dir)
{
  
  switch(dir){
  case DOWN:
    if(board.empty(x,y-1))
      y--;
    break;
  case UP:
    if(board.empty(x,y+1))
      y++;
    break;
  case RIGHT:
    if(board.empty(x+1,y))
      x++;
    break;
  case LEFT:
    if(board.empty(x-1,y))
      x--;
    break;
  case PASS:
    break;
  default:
    LOG_ERROR("Movement Failed!");
    break;
  }
  
}

ostream& operator << (ostream &os, const Player p)
{
  os << p.x << " " << p.y;
  
  return os;
}
