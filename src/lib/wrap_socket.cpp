#include "./unp.h"

int Socket(int domain, int type, int protocol)
{
	int n;
	if ((n = socket(domain, type, protocol)) < 0)
	{
		LogErrQuit("Socket error.");
	}

	return n;
}

void  Bind(int sock_fd, const struct sockaddr * addr, int sock_len)
{
	if ( bind(sock_fd, addr, sock_len) < 0)
	{
		LogErrQuit("Bind error.");
	}
}

void Listen(int sock_fd, int backlog)
{
	char *ptr;

	// 允许管理员自己设置backlog的值，atoi函数将字符串转为整型值
	if ((ptr = getenv("LISTENQ")) != NULL)
	{
		backlog = atoi(ptr);
	}

	if (listen(sock_fd, backlog) != 0)
	{
		LogErrQuit("Listen Error.");
	}
}

int Accept(int sock_fd, struct sockaddr * addr, int *)
{

}
