
#ifndef __AIINTERFACE_H__
#define __AIINTERFACE_H__


#include <string>

#include "player.h"

using namespace std;

class AIInterface
{
 public:

  pid_t pid;
  string executablePath;
  string name;
  string socketName;
  string action;

  int connection_fd;

  AIInterface(string execPath);
  ~AIInterface();

  int StartClientAi();

  int connection_handler(int connection_fd);

  int StartServer();

  int Start();

  template <class DataType> AIInterface& operator<< (const DataType& variable);

  template <class DataType> AIInterface& operator>> (DataType& variable);

  PlayerMotionType getMovement();
};

#endif
