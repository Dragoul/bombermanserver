

#define LOG(type, msg, ...)						\
  do {									\
    fprintf(stderr,"\033[34;1m%s\033[0m: %d : %s (%d) : ", __FILE__, __LINE__, type, getpid()); \
    fprintf(stderr,msg, ##__VA_ARGS__);					\
    fprintf(stderr,"\n");						\
  } while(0)

#define LOG_ERROR(msg, ...) LOG("\033[31mERROR\033[0m", msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) LOG("\033[33mWARNING \033[0m", msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) LOG("\033[32mNOTE\033[0m", msg, ##__VA_ARGS__)


#include <iostream>

void gotoxy(int x, int y)
{
  //  printf("\033[%d;%df",y,x);
  //  std::cout << std::flush;

  std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

void cls()
{
  std::cout << "\033[2J" << std::flush;
}
