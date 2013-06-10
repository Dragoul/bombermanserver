

#include <iostream>

void gotoxy(int x, int y)
{
  std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

void cls()
{ 
  std::cout << "\033[2J" << std::flush;
}
