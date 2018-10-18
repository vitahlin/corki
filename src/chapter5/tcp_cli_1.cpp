
#include "./../lib/unp.h"

void StringCli(FILE *fp, int sock_fd)
{
	int n;
	char send_line[MAX_LINE];
	char receive_line[MAX_LINE];

	while (cin >> send_line)
	{
		cout << "Input: " << send_line << endl;
		Write(sock_fd, send_line, MAX_LINE);

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
	}
}

int main(int argc, char *argv[])
{
	int n;
	int sock_fd;
	char send_str[MAX_LINE];
	char receive_str[MAX_LINE];
	struct sockaddr_in sock_addr;

	if (argc != 2)
	{
		LogErrQuit("Param error.");
	}

	sock_fd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&sock_addr, sizeof(sock_addr));

	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(9876);
	InetPton(AF_INET, argv[1], &sock_addr.sin_addr);

	Connect(sock_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));

	StringCli(stdin, sock_fd);

	return 0;
}
