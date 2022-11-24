#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAXLINE 4096

// macOS上面可能会出现 SIGCLD 找不到的情况
#ifndef SIGCLD
#define SIGCLD SIGCHLD
#endif

// 错误打印函数封装，在log_err.cpp
void ErrorSystem(const char *fmt, ...);

void ErrorQuit(const char *fmt, ...);

void ErrorReturn(const char *fmt, ...);

// 信号相关，tellwait.cpp
void TELL_WAIT();

void TELL_CHILD(pid_t);

void TELL_PARENT(pid_t);

void WAIT_CHILD();

void WAIT_PARENT();

int MySystem(const char *);

void PrintExit(int status);