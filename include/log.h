

#define LOG(type, msg, ...)						\
  do {									\
    printf("\033[34m%s\033[0m: %d : %s: ", __FILE__, __LINE__, type); \
    printf(msg, ##__VA_ARGS__);					      \
    printf("\n");						      \
  } while(0)

#define LOG_ERROR(msg, ...) LOG("\033[31mERROR   \033[0m", msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) LOG("\033[33mWARNING \033[0m", msg, ##__VA_ARGS__)
#define LOG_NOTE(msg, ...) LOG("\033[32mNOTE    \033[0m", msg, ##__VA_ARGS__)

