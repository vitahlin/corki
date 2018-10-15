/*============================================================================
* Created       : 2018-10-15 16:55
* Last modified : 2018-10-15 16:55
* Filename      : day_time_tcp_srv.cpp
* Description   :
*   获取时间服务器程序，原书代码intro/daytimetcpsrv.c
*
=============================================================================*/

#include "./../lib/unp.h"
#include <time.h>

int main(int argc, char *argv[])
{
	int listen_fd = 0;
	int conn_fd;

	struct sockaddr_in serv_addr;

	struct sockaddr_in client_addr;
	int client_addr_length;

	char send_line[MAX_LINE + 1];

	char client_addr_str[MAX_LINE];

	time_t ticks;

	listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

	// 将对应字节全部置0
	bzero(&serv_addr, sizeof(serv_addr));

	// 协议族
	serv_addr.sin_family = AF_INET;

	// INADDR_ANY 指定0.0.0.0的地址，表示本机所有IP
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// 端口指定
	serv_addr.sin_port = htons(9876);

	// 对套接字进行地址和端口绑定
	Bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	Listen(listen_fd, LISTENQ);

	cout << "Server is running..." << endl;
	for (;;)
	{
		client_addr_length  = sizeof(client_addr);
		conn_fd = Accept(listen_fd, (struct sockaddr *)&client_addr, (unsigned int *) &client_addr_length);

		InetNtop( AF_INET, &client_addr.sin_addr, client_addr_str, sizeof(client_addr_str));
		cout << "Client IP: " <<  client_addr_str << endl;
		//cout << "Client port: " << client_addr.sin_port << endl;

		ticks = time(NULL);
		snprintf(send_line, sizeof(send_line), "%.24s\r\n", ctime(&ticks));
		Write(conn_fd, send_line, sizeof(send_line));
		Close(conn_fd);
	}

	return 0;
}
