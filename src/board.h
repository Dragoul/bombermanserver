
#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>
#include <vector>

using namespace std;


class Board
{
public:
  vector<string> area;

  Board();
  
  Board(string filePath);
  
  ~Board();
  
  void Load(string filePath);

  bool isEmpty(int x, int y);
  
  int empty(int x,int y);

};

ostream& operator << (ostream &os, const Board& map);

#endif
