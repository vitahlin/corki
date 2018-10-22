
#include "./../lib/unp.h"

void StringCli(FILE *fp, int sockfd)
{
	char    sendline[MAXLINE], recvline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL)
	{

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
		{
			LogErrQuit(""str_cli: server terminated prematurely");
		}

		Fputs(recvline, stdout);
	}
}

int main(int argc, char *argv[])
{
	int n;
	int sock_fd;
	char send_str[MAXLINE];
	char receive_str[MAXLINE];
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
