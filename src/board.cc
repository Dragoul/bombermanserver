

#include <iostream>


#include "board.h"

Board::Board()
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

Board::Board(string filePath)
{
}

Board::~Board()
{
}

void Board::Load(string filePath)
{
}

bool Board::isEmpty(int x, int y)
{
  return true;
}

int Board::empty(int x,int y)
{
  string line = area[y];
  return line[x] = '.';
}


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
