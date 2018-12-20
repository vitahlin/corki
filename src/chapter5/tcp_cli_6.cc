
#include "./../lib/constant.h"
#include "./../lib/unp.h"

void StrCli(FILE* fp, int sock_fd) {
    char send_line[MAXLINE];
    char receive_line[MAXLINE];

    while (Fgets(send_line, MAXLINE, fp) != NULL) {
        Writen(sock_fd, send_line, strlen(send_line));

        if (Readline(sock_fd, receive_line, MAXLINE) == 0) {
            LogErrQuit("StrCli: Server terminated prematurely");
        }

        // Fputs(receive_line, stdout);
        cout << "Received from server: " << receive_line;
    }
}

int main(int argc, char* argv[]) {
    int n;
    int sock_fd;
    char send_str[MAXLINE];
    char receive_str[MAXLINE];
    struct sockaddr_in sock_addr;

    if (argc != 2) {
        LogErrQuit("Param error.");
    }

    sock_fd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&sock_addr, sizeof(sock_addr));

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(9876);
    InetPton(AF_INET, argv[1], &sock_addr.sin_addr);

    Connect(sock_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr));

    cout << "Client is running..." << endl;
    StrCli(stdin, sock_fd);

    return 0;
}
