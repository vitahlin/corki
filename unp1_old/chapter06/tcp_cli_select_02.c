#include "../lib/unp.h"

void strCli(FILE *fp, int sock_fd) {
    int max_fdp, n;
    fd_set read_set;
    char buff[MAX_SIZE];
    FD_ZERO(&read_set);

    // 标记为0表示当前可读
    int stdin_eof = 0;
    for (;;) {
        if (stdin_eof == 0) {
            FD_SET(sock_fd, &read_set);
        }

        FD_SET(fileno(fp), &read_set);

        max_fdp = max(fileno(fp), sock_fd) + 1;
        wrapSelect(max_fdp, &read_set, NULL, NULL, NULL);

        // socket当前可读
        if (FD_ISSET(sock_fd, &read_set)) {
            if ((n = wrapReadlineV2(sock_fd, buff, MAX_SIZE)) == 0) {
                if (stdin_eof == 1) {
                    return;
                } else {
                    printfAndQuit("str_cli: server terminated prematurely");
                }
            }
            wrapFputs(buff, stdout);
        }

        // 当前可写
        if (FD_ISSET(fileno(fp), &read_set)) {
            if ((n = wrapReadlineV2(fileno(fp), buff, MAX_SIZE)) == 0) {
                stdin_eof = 1;

                // 发送FIN
                wrapShutdown(sock_fd, SHUT_WR);
                FD_CLR(fileno(fp), &read_set);
                continue;
            }

            wrapWriten(sock_fd, buff, n);
        }
    }
}

int main(int argc, char **argv) {
    int sock_fd;
    struct sockaddr_in serv_address;

    char serv_ip[16] = "127.0.0.1";
    int port = 9876;

    // 创建一个套接字
    sock_fd = wrapSocket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_address, sizeof(serv_address));

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(port);

    wrapInetPton(AF_INET, serv_ip, &serv_address.sin_addr);
    wrapConnect(sock_fd, (const struct sockaddr *) &serv_address, sizeof(serv_address));

    strCli(stdin, sock_fd);

    return 0;
}