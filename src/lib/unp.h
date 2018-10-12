#include <iostream>
#include <netinet/in.h>
using namespace std;


#define MAX_LINE 4096

// 错误打印函数封装，封装在log_err.cpp文件
void LogErrQuit(string str);
void LogErr(string str);

// socket相关函数封装，在wrap_socket.cpp文件
int Socket(int domain, int type, int protocol);
