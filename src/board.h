
#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Board
{
public:
  vector<string> area;

  Board()
  {
      area.push_back("#########");
      area.push_back("####.####");
      area.push_back("#...+...#");
      area.push_back("#...+...#");
      area.push_back("#...+...#");
      area.push_back("#.#.#.#.#");
      area.push_back("#++###++#");
      area.push_back("#.#####.#");
      area.push_back("#++###++#");
      area.push_back("#.#.#.#.#");
      area.push_back("#...+...#");
      area.push_back("#...+...#");
      area.push_back("#...+...#");
      area.push_back("####.####");
      area.push_back("#########");
    }
  
  Board(string filePath)
  {
  }
  
  ~Board()
  {
  }
  
  void Load(string filePath)
  {
  }

  bool isEmpty(int x, int y)
  {
    return true;
  }
};

ostream& operator << (ostream &os, const Board& map)
{
  for(vector<string>::const_iterator itr = map.area.begin();
      itr < map.area.end();
      ++itr)
    {
      os << *itr << "\n";
    }
  
  return os;
}

#endif
