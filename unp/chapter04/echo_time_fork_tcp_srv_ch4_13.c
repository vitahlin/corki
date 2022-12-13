/**
 * 返回时间的服务器程序
 * 采用fork函数并发处理
 */
#include <time.h>
#include "../lib/unp.h"

int main(int argc, char **argv) {
    int conn_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len;
    char buff[MAX_SIZE];
    time_t ticks;
    pid_t pid;

    int listen_fd = wrapSocket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9901);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    wrapBind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    // 将套接字转换成一个监听套接字，这样来自客户端的外来连接就可以在该套接字上由内核接受
    wrapListen(listen_fd, LISTENQ);

    printf("time server running...\n");
    for (;;) {
        conn_fd = wrapAccept(listen_fd, (struct sockaddr *) &cli_addr, &len);

        // 采用fork函数并发处理
        if ((pid = fork()) < 0) {
            perror("fork error");
            exit(-1);
        } else if (pid == 0) {
            // 子进程处理客户端连接逻辑
            wrapClose(listen_fd);

            printf("New client connect IP=%s, port=%d, conn_id=%d\n",
                   inet_ntop(AF_INET, &cli_addr.sin_addr, buff, sizeof(buff)),
                   ntohs(cli_addr.sin_port),
                   conn_fd);
            ticks = time(NULL);

            snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
            wrapWriten(conn_fd, buff, sizeof(buff));
            wrapClose(conn_fd);
            exit(0);
        }

        /**
         * 父进程关闭，这里为什么不会关闭连接？
         * 因为每个文件或者套接字都有一个引用计数，引用计数在文件表项中维护，它是当前打开着的引用该文件或套接字的描述符的个数。
         * socket返回后与listen_fd关联的文件表项的引用计数值为1。
         * accept返回后与conn_fd关联的文件表项的引用计数值也为1。
         * 然而fork返回后，这两个描述符就在父进程与子进程间共享(也就是被复制)，因此与这两个套接字相关联的文件衣项各自的访问计数值均为2。
         * 这么一来，当父进程关闭conn_fd时，它只是把相应的引用计数值从2减为1。
         * 该套接字真正的清理和资源释放要箩到其引用计数值到达0时才发生。
         * 这会在稍后子进程也关闭conn_td时发生
         */
        wrapClose(conn_fd);
    }

    return 0;
}