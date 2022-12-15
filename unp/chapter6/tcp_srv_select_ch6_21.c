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
        printfAndQuit("read error");
    }
}

int main(int argc, char **argv) {
    int listen_fd, conn_fd, sock_fd;
    int i, max_index, max_fd, n;

    int client_ip[16];

    // 就绪的描述符数量
    int ready_fd_count;

    int client[FD_SETSIZE];
    socklen_t client_len;
    char receive_line[MAX_SIZE];
    struct sockaddr_in serv_address, cli_address;
    fd_set read_set, all_set;

    listen_fd = wrapSocket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_address, sizeof(serv_address));
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(7777);
    serv_address.sin_addr.s_addr = htonl(INADDR_ANY);

    wrapBind(listen_fd, (const struct sockaddr *) &serv_address,
             sizeof(serv_address));
    wrapListen(listen_fd, LISTENQ);

    max_fd = listen_fd;
    max_index = -1;

    // 初始化为-1表示没有
    for (i = 0; i < FD_SETSIZE; i++) {
        client[i] = -1;
    }

    FD_ZERO(&all_set);
    FD_SET(listen_fd, &all_set);

    for (;;) {
        read_set = all_set;

        /**
         * select等待某个事件的发生：新客户连接的建立，或是数据、FIN或RST的到达
         * 这里timeout参数为空指针，会一直等待
         */
        ready_fd_count = wrapSelect(max_fd + 1, &read_set, NULL, NULL, NULL);
        printf("select ready count=%d\n", ready_fd_count);

        // 如果监听套接字变为可读，说明这时候有一个客户端尝试连接
        if (FD_ISSET(listen_fd, &read_set)) {
            client_len = sizeof(cli_address);
            conn_fd = wrapAccept(listen_fd, (struct sockaddr *) &cli_address, &client_len);

            // 取client数组第一个未用项记录这个连接描述符
            for (i = 0; i < FD_SETSIZE; i++) {
                if (client[i] < 0) {
                    printf("Accept new client connect IP=%s, port=%d, conn_id=%d, index=%d\n",
                           inet_ntop(AF_INET, &cli_address.sin_addr, (char *) &client_ip, sizeof(client_ip)),
                           ntohs(cli_address.sin_port),
                           conn_fd,
                           i);
                    client[i] = conn_fd;
                    break;
                }
            }

            // client数组不存在-1值，当前客户端连接已经超过最大值
            if (i == FD_SETSIZE) {
                printfAndQuit("too many clients ");
            }

            FD_SET(conn_fd, &all_set);

            if (conn_fd > max_fd) {
                max_fd = conn_fd;
            }

            if (i > max_index) {
                max_index = i;
            }

            // 就绪描述符小于0，没有更多的可读文件描述符
            if (--ready_fd_count <= 0) {
                continue;
            }
        }

        /**
         * 对于现有的每个客户端连接，都测试描述符是否在select返回的描述符集合中.
         * 如果是就从客户读取一行文本并回射给它，如果客户关闭了连接，那么read将返回0，更新数据结构
         */
        for (i = 0; i <= max_index; i++) {
            if ((sock_fd = client[i]) < 0) {
                continue;
            }

            if (FD_ISSET(sock_fd, &read_set)) {
                // 客户端关闭了连接，更新数据结构
                if ((n = wrapReadlineV2(sock_fd, receive_line, MAX_SIZE)) == 0) {
                    wrapClose(sock_fd);
                    FD_CLR(sock_fd, &all_set);
                    client[i] = -1;
                } else {
                    printf("index %d receive from client: %s", i, receive_line);
                    wrapWriten(sock_fd, receive_line, n);
                }

                if (--ready_fd_count <= 0) {
                    break;
                }
            }
        }
    }
}