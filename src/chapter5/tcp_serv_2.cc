
#include "./../lib/constant.h"
#include "./../lib/unp.h"

void StrEcho(int sock_fd) {
    int n;
    char line[MAXLINE];

    for (;;) {
        if ((n = Readline(sock_fd, line, MAXLINE)) == 0) {
            return;
        }
        cout << "Received from client: " << line;
        Writen(sock_fd, line, n);
    }
}

int main(int argv, char* argc[]) {
    int conn_fd, listen_fd;
    struct sockaddr_in srv_addr;

    int pid;

    listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&srv_addr, sizeof(srv_addr));

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(9876);

    Bind(listen_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    Listen(listen_fd, LISTENQ);

    cout << "Server is running..." << endl;
    for (;;) {
        conn_fd = Accept(listen_fd, NULL, NULL);
        if ((pid = Fork()) == 0) {
            Close(listen_fd);
            StrEcho(conn_fd);
            Close(conn_fd);
            exit(0);
        }
        Close(conn_fd);
    }

    return 0;
}
