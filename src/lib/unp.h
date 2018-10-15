// socket函数需要头文件
#include <netinet/in.h>

// htonl函数需要头文件
#include <arpa/inet.h>

// bind、listen函数需要头文件
#include<sys/types.h>
#include<sys/socket.h>

// write函数所需头文件
#include<unistd.h>

#include<stdio.h>

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
void Bind(int sock_fd, const struct sockaddr * addr, int sock_len);
int Accept(int sock_fd, struct sockaddr * client_addr, unsigned int * addr_length);
void InetPton(int af, const char *src, void *dst);
void Connect(int sock_fd, struct sockaddr * serv_addr, int addr_length);

// unix相关函数封装，在wrap_unix.cpp
void Write(int fd, const void *buff, int count);
