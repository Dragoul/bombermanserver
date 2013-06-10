#ifndef __LOG_H__
#define __LOG_H__


#define LOG(type, msg, ...)						\
  do {									\
    fprintf(stderr,"\033[34;1m%s\033[0m: %d : %s (%d) : ", __FILE__, __LINE__, type, getpid()); \
    fprintf(stderr,msg, ##__VA_ARGS__);					\
    fprintf(stderr,"\n");						\
  } while(0)

#define LOG_ERROR(msg, ...) LOG("\033[31mERROR\033[0m", msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) LOG("\033[33mWARNING \033[0m", msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) LOG("\033[32mNOTE\033[0m", msg, ##__VA_ARGS__)


void gotoxy(int x, int y);
void cls();

#endif

