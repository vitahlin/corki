/*============================================================================
* Created       : 2018-10-15 16:59
* Last modified : 2018-10-15 16:59
* Filename      : exercise_1_4_cli.cpp
* Description   :
*   第一章习题1.4
*
=============================================================================*/

#include "./../lib/unp.h"

int main(int argc, char* argv[])
{
	int n, sock_fd;
	char recv_line[MAX_LINE + 1];

	struct sockaddr_in serv_addr;

	int read_count = 0;

	// 判断参数个数是否正确
	if (argc != 2)
	{
		LogErrQuit("param error");
	}

	sock_fd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(9876);
	InetPton(AF_INET, argv[1], &serv_addr.sin_addr);

	Connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	while ((n = read(sock_fd, recv_line, MAX_LINE)) > 0)
	{
		read_count++;
		recv_line[n] = 0;
		if (fputs(recv_line, stdout) == EOF)
		{
			LogErr("fputs error");
		}
	}
	if (n < 0)
	{
		LogErr("read error");
	}

	cout << "Read count:" << read_count << endl;
	exit(0);

	return 0;
}
