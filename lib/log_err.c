#include <errno.h>
#include <stdarg.h>
#include "./apue.h"

static void ErrorDoIt(int, int, const char*, va_list);

void ErrorReturn(const char* fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    ErrorDoIt(1, errno, fmt, ap);
    va_end(ap);
}

void ErrorSystem(const char* fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    ErrorDoIt(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

void ErrorQuit(const char* fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    ErrorDoIt(0, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

static void ErrorDoIt(int errnoflag, int error, const char* fmt, va_list ap) {
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (errnoflag) {
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s",
                 strerror(error));
    }

    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);
}