#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

int main() {

    struct addrinfo hints, *result, *p;
    int status;

    // 设置hint结构体数据全为0，不然可能出现随机值
    memset(&hints, 0, sizeof(hints));

    // 不限制IPv4 IPv6
    hints.ai_family = AF_UNSPEC;

    // TCP套接字类型
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo("www.baidu.com", "http", &hints, &result)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 1;
    }

    // 遍历所有返回的地址信息
    for (p = result; p != NULL; p = p->ai_next) {
        void *addr;
        char ip_str[INET6_ADDRSTRLEN];

        // 获取对应的IPv4或IPv6地址
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(p->ai_family, addr, ip_str, sizeof(ip_str));
        printf("IP address:%s\n", ip_str);
    }

    freeaddrinfo(result); // 释放内存

    return 0;
}
