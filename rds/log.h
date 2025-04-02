#include <stdarg.h>
#include <stdio.h>
#include <time.h>


#define LOG_INFO    1
#define LOG_WARNING 2
#define LOG_ERROR   3


void loggerError(const char *message, ...);
void logger(int level, const char *message, ...);