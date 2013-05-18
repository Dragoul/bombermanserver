
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

class Player
{
 public:

  int alive;
  int x;
  int y;

  int outputFd; // standard input for ai
  int inputFd;  // standard output for ai
  int logsFd;   // standard error for ai

  std::string exeFileName;


  int move(Board board, std::string dir);

};

#endif
