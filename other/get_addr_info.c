#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/socket.h>

void getCanUsedIpAddressInLocalhost() {
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    struct sockaddr_in *sinp;
    char *hostname = "localhost";
    char buf[INET_ADDRSTRLEN];
    char *server = "6543"; /* 这是服务端口号 */
    const char *addr;
    int ilRc;

    hint.ai_family = AF_UNSPEC; /* hint 的限定设置 */
    hint.ai_socktype = 0; /* 这里可是设置 socket type . 比如 SOCK——DGRAM */
    hint.ai_flags = AI_PASSIVE; /* flags 的标志很多 。常用的有AI_CANONNAME; */
    hint.ai_protocol = 0; /* 设置协议 一般为0，默认 */
    hint.ai_addrlen = 0; /* 下面不可以设置，为0，或者为NULL */
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    ilRc = getaddrinfo(hostname, server, &hint, &ailist);
    if (ilRc < 0) {
        printf("str_error = %s\n", gai_strerror(errno));
        return;
    }

    /* 显示获取的信息 */
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        sinp = (struct sockaddr_in *) aip->ai_addr;
        addr = inet_ntop(AF_INET, &sinp->sin_addr, buf, INET_ADDRSTRLEN);
        printf(" addr = %s, port = %d\n", addr ? addr : "unknow ", ntohs(sinp->sin_port));
    }
}

void getIpByHostname() {
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
        return;
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
}


int main() {
    printf("\ngetIpByHostname:\n");
    getIpByHostname();

    printf("\ngetCanUsedIpAddressInLocalhost:\n");
    getCanUsedIpAddressInLocalhost();
    return 0;
}
