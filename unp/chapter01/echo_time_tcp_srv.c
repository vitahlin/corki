/**
 * 返回时间的服务器程序
 */
#include <time.h>
#include "../lib/constant.h"
#include "../lib/unp.h"

int main(int argc, char **argv) {
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len;
    char buff[MAX_SIZE];
    time_t ticks;

    // SOCK_STREAM套接字类型
    int listen_fd = wrapSocket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));

    // 协议族，AF_INET表示IPv4协议
    serv_addr.sin_family = AF_INET;

    // 套接字端口
    serv_addr.sin_port = htons(9876);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    wrapBind(listen_fd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // 将套接字转换成一个监听套接字，这样来自客户端的外来连接就可以在该套接字上由内核接受
    wrapListen(listen_fd, LISTENQ);

    printf("time server running...\n");
    for (;;) {
        // 调用accept返回用于传输的socket的文件描述符
        int conn_fd = wrapAccept(listen_fd, (struct sockaddr *) &cli_addr, &len);

        printf("New client connect IP=%s, port=%d, conn_id=%d\n",
               inet_ntop(AF_INET, &cli_addr.sin_addr, buff, sizeof(buff)),
               ntohs(cli_addr.sin_port),
               conn_fd);
        ticks = time(NULL);

        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        wrapWriten(conn_fd, buff, sizeof(buff));

        wrapClose(conn_fd);
    }
}