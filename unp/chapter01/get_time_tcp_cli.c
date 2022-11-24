/**
 * 获取时间
 */
#include "../lib/constant.h"
#include "../lib/unp.h"

int main(int argc, char **argv) {
    char serv_ip[16];
    int port;

    // 网络上可用的时间服务器IP地址132.163.96.5，端口13
    printf("Input IP address: ");
    scanf("%s", serv_ip);
    printf("Input port: ");
    scanf("%d", &port);

    // 创建一个套接字
    int sock_fd = wrapSocket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_address;
    bzero(&serv_address, sizeof(serv_address));

    // 协议族
    serv_address.sin_family = AF_INET;
    // 指定端口，时间服务器端口13
    serv_address.sin_port = htons(port);

    // 进行IP地址转换
    wrapInetPton(AF_INET, serv_ip, &serv_address.sin_addr);

    wrapConnect(sock_fd, (const struct sockaddr *) &serv_address, sizeof(serv_address));

    ssize_t n;
    char receive_line[MAX_SIZE + 1];
    while ((n = read(sock_fd, receive_line, MAX_SIZE)) > 0) {
        receive_line[n] = 0;
        if (fputs(receive_line, stdout) == EOF) {
            printf("fputs error");
            exit(-1);
        }
    }

    if (n < 0) {
        printf("read error");
        exit(-1);
    }

    return 0;
}