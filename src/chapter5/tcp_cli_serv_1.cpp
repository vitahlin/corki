
#include "./../lib/unp.h"

void StringEcho(int sock_fd)
{
	int n;
	char line[MAX_LINE];

	while ((n = read(sock_fd, line, MAX_LINE)) > 0)
	{
		Write(sock_fd, line, n);
	}
	if (n < 0)
	{
		LogErrQuit("Read error.");
	}

}

int main(int argv, char *argc[])
{
	int conn_fd, listen_fd;
	struct sockaddr_in srv_addr;

	int pid;

	listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&srv_addr, sizeof(srv_addr));

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(9876);

	Bind(listen_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	Listen(listen_fd, LISTENQ);

	for (;;)
	{
		conn_fd = Accept(listen_fd, NULL, NULL);
		if ((pid = Fork()) == 0)
		{
			Close(listen_fd);
			StringEcho(conn_fd);
			Close(conn_fd);
			exit(0);
		}
		Close(conn_fd);
	}

	return 0;
}
