// socket函数需要头文件
#include <netinet/in.h>

// htonl函数需要头文件
#include <arpa/inet.h>

// bind、listen函数需要头文件
#include <sys/socket.h>
#include <sys/types.h>

// write函数所需头文件
#include <unistd.h>

#include <stdio.h>

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define socklen_t unsigned int

// 错误打印函数封装，在log_err.cc
void LogErr(string str);
void LogErrQuit(string str);

// socket相关函数封装，在wrap_socket.cc
int Socket(int domain, int type, int protocol);
void Listen(int sock_fd, int backlog);
void Bind(int sock_fd, const struct sockaddr *addr, socklen_t sock_len);
int Accept(int sock_fd, struct sockaddr *client_addr, socklen_t *addr_length);
void Connect(int sock_fd, struct sockaddr *serv_addr, socklen_t addr_length);
void InetPton(int af, const char *src, void *dst);
const char *InetNtop(int family,
                     const void *addr_ptr,
                     char *str_ptr,
                     size_t length);

// unix相关函数封装，在wrap_unix.cc
void Write(int fd, const void *buff, int count);
void Close(int fd);
int Fork();

// 写函数封装
int writen(int fd, const void *ptr, int n);
void Writen(int fd, void *ptr, int nbytes);

// 读函数封装
int readline(int fd, void *vptr, int maxlen);
int Readline(int fd, void *ptr, int maxlen);

// C输出输出相关函数封装，在wrap_stdio.cc
char *Fgets(char *ptr, int n, FILE *stream);
void Fputs(const char *ptr, FILE *stream);
