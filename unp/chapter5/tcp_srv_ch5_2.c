/**
 * 回射程序的服务端
 * fork子进程处理客户端连接
 */
#include "../lib/unp.h"

void strEcho(int sock_fd) {
    ssize_t n;
    char buf[MAX_SIZE];

    again:
    bzero(buf, MAX_SIZE);
    while ((n = read(sock_fd, buf, MAX_SIZE)) > 0) {
        wrapWriten(sock_fd, buf, n);
    }
    if (n < 0 && errno == EINTR) {
        goto again;
    } else if (n < 0) {
        perror("read error");
    }
}


int main(int argc, char **argv) {
    int conn_fd;
    struct sockaddr_in serv_address, cli_address;
    socklen_t len;
    pid_t child_pid;

    int listen_fd = wrapSocket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_address, sizeof(serv_address));

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(9876);
    serv_address.sin_addr.s_addr = htonl(INADDR_ANY);

    wrapBind(listen_fd, (const struct sockaddr *) &serv_address, sizeof(serv_address));

    // 将套接字转换成一个监听套接字，这样来自客户端的外来连接就可以在该套接字上由内核接受
    wrapListen(listen_fd, LISTENQ);

    for (;;) {
        len = sizeof(cli_address);
        conn_fd = wrapAccept(listen_fd, (struct sockaddr *) &cli_address, &len);

        /**
         * 采用fork函数并发处理
         * 客户端进程关闭时，无法处理服务器进程僵死的情况，因为没有默认的SIGCHLD是被忽略的
         */
        if ((child_pid = fork()) < 0) {
            perror("fork error");
            exit(-1);
        } else if (child_pid == 0) {
            // 子进程处理客户端连接逻辑
            wrapClose(listen_fd);

            strEcho(conn_fd);
            exit(0);
        }
        wrapClose(conn_fd);
    }
}