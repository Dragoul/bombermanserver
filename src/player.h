
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
using namespace std;

#include <string>

#include "board.h"

typedef enum{
  PASS = 0,
  DOWN,
  UP,
  RIGHT,
  LEFT
} PlayerMotionType;

class Player
{
 public:

  int alive;
  int x;
  int y;

  int outputFd; // standard input for ai
  int inputFd;  // standard output for ai
  int logsFd;   // standard error for ai

  string exeFileName;

  Player(int x_, int y_);
  
  ~Player();

  int move(Board board, PlayerMotionType dir);

};

ostream& operator << (ostream &os, const Player p);

#endif
