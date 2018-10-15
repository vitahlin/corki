#include "./../lib/unp.h"

int main(int argc, char *argv[])
{
	int n;
	int sock_fd;
	char receive_line[MAX_LINE + 1];

	struct sockaddr_in sock_addr;

	if (argc != 2)
	{
		LogErrQuit("Param error");
	}

	sock_fd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&sock_addr, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(9876);

	// 将要连接的服务器IP地址进行转换，并赋值
	InetPton(AF_INET, argv[1], &sock_addr.sin_addr);

	Connect(sock_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));

	while ((n = read(sock_fd, receive_line, MAX_LINE)) > 0)
	{
		receive_line[n] = 0;
		if (fputs(receive_line, stdout) == EOF)
		{
			LogErr("Fputs error");

		}
	}
	if (n < 0)
	{
		LogErrQuit("Read error");
	}


	return 0;
}
