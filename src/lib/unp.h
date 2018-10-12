// socket函数需要头文件
#include <netinet/in.h>

// htonl函数需要头文件
#include <arpa/inet.h>

// bind、listen函数需要头文件
#include<sys/types.h>
#include<sys/socket.h>

#include <iostream>
using namespace std;


#define MAX_LINE 4096

#define LISTENQ 1024

// 错误打印函数封装，封装在log_err.cpp文件
void LogErrQuit(string str);
void LogErr(string str);

// socket相关函数封装，在wrap_socket.cpp文件
int Socket(int domain, int type, int protocol);
void Listen(int sock_fd, int backlog);
void  Bind(int sock_fd, const struct sockaddr * addr, int sock_len);
