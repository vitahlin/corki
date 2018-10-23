#include "./unp.h"

int Socket(int domain, int type, int protocol) {
    int n;
    if ((n = socket(domain, type, protocol)) < 0) {
        LogErrQuit("Socket error.");
    }

    return n;
}

void Bind(int sock_fd, const struct sockaddr *addr, unsigned int sock_len) {
    if (bind(sock_fd, addr, sock_len) < 0) {
        LogErrQuit("Bind error.");
    }
}

void Listen(int sock_fd, int backlog) {
    char *ptr;

    // 允许管理员自己设置backlog的值，atoi函数将字符串转为整型值
    if ((ptr = getenv("LISTENQ")) != NULL) {
        backlog = atoi(ptr);
    }

    if (listen(sock_fd, backlog) != 0) {
        LogErrQuit("Listen Error.");
    }
}

int Accept(int sock_fd,
           struct sockaddr *client_addr,
           unsigned int *addr_length) {
    int n;
    if ((n = accept(sock_fd, client_addr, addr_length)) < 0) {
        LogErrQuit("Accept error");
    }

    return n;
}

void Connect(int sock_fd, struct sockaddr *serv_addr, socklen_t addr_length) {
    if (connect(sock_fd, serv_addr, addr_length) < 0) {
        LogErrQuit("Connect error");
    }
}

void InetPton(int af, const char *src, void *dst) {
    if (inet_pton(af, src, dst) <= 0) {
        LogErrQuit("InetPton error");
    }
}

const char *InetNtop(int family,
                     const void *addr_ptr,
                     char *str_ptr,
                     size_t length) {
    const char *ptr;
    if ((ptr = inet_ntop(family, addr_ptr, str_ptr, length)) == NULL) {
        LogErrQuit("inetNtop error");
    }
    return ptr;
}
