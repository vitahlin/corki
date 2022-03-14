#include "../lib/unp.h"

void strCli(FILE *fp, int sock_fd) {
    int max_fdp;
    fd_set read_set;
    char send_line[MAX_SIZE], receive_line[MAX_SIZE];
    FD_ZERO(&read_set);
    for (;;) {
        FD_SET(fileno(fp), &read_set);
        FD_SET(sock_fd, &read_set);

        max_fdp = max(fileno(fp), sock_fd) + 1;
        wrapSelect(max_fdp, &read_set, NULL, NULL, NULL);

        // socket当前可读
        if (FD_ISSET(sock_fd, &read_set)) {
            if (wrapReadlineV2(sock_fd, receive_line, MAX_SIZE) == 0) {
                printfAndQuit("str_cli: server terminated prematurely ");
            }
            printf("receive from server:%s", receive_line);
            wrapFputs(receive_line, stdout);
        }

        // 当前可写
        if (FD_ISSET(fileno(fp), &read_set)) {
            if (wrapFgets(send_line, MAX_SIZE, fp) == NULL) {
                return;
            }

            wrapWriten(sock_fd, send_line, strlen(send_line));
        }
    }
}

int main(int argc, char **argv) {
    char serv_ip[16] = "127.0.0.1";
    int port = 7777;

    int sock_fd;
    struct sockaddr_in serv_address;

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