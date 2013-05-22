

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

int Player::move(Board board, Motion dir)
{

  switch(dir){
  case DOWN:
    if(board.free(x,y-1))
      y-;
    break;
  case UP:
    if(board.free(x,y+1))
      y-1;
    break;
  case RIGHT:
    if(board.free(x+1,y))
      x++;
    break;
  case LEFT:
    if(board.free(x-1,y))
      x--;
    break;
  case PASS:
    break;
  default:
    break;
  }
}
