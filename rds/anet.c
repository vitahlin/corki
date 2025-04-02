
#include "anet.h"
#include "server.h"
#include "log.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>


int anetListen(int s, struct sockaddr *sa, socklen_t len, int backlog) {
    if (bind(s, sa, len) == -1) {
        logger(LOG_ERROR, "bind: %s", strerror(errno));
        close(s);
        return RDS_ERROR;
    }

    if (listen(s, backlog) == -1) {
        logger(LOG_ERROR, "listen: %s", strerror(errno));
        close(s);
        return RDS_ERROR;
    }
    return RDS_OK;
}

int anetSetBlock(char *err, int fd, int non_block) {
    int flags;

    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        loggerError(err, "fcntl(F_GETFL): %s", strerror(errno));
        return RDS_ERROR;
    }

    if (!!(flags & O_NONBLOCK) == !!non_block)
        return RDS_OK;

    if (non_block)
        // 设置非阻塞模式
        flags |= O_NONBLOCK;
    else
        // 设置阻塞模式
        flags &= ~O_NONBLOCK;

    // fcntl(fd, F_SETFL, flags) 用于更新文件描述符 fd 的状态。
    if (fcntl(fd, F_SETFL, flags) == -1) {
        loggerError(err, "fcntl(F_SETFL,O_NONBLOCK): %s", strerror(errno));
        return RDS_ERROR;
    }
    return RDS_OK;
}


int anetTcpServer(char *server_net_error, int port, char *bindaddr, int backlog) {
    struct addrinfo hint, *p, *serv_addr_info;
    int status, socket_fd = -1;
    char _port[6];
    snprintf(_port, 6, "%d", port);

    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, _port, &hint, &serv_addr_info)) != 0) {
        logger(LOG_ERROR, gai_strerror(status));
        return RDS_ERROR;
    }

    for (p = serv_addr_info; p != NULL; p = p->ai_next) {
        if ((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            logger(LOG_ERROR, "socket: %s", strerror(socket_fd));
            continue;
        }

        if (anetListen(socket_fd, p->ai_addr, p->ai_addrlen, backlog) == RDS_ERROR) {
            socket_fd = RDS_ERROR;
        }
        goto end;
    }
    if (p == NULL) {
        logger(LOG_ERROR, "unable to bind socket, errno: %d", errno);
        goto error;
    }

error:
    if (socket_fd != -1) {
        close(socket_fd);
    }
    socket_fd = RDS_ERROR;
end:
    freeaddrinfo(serv_addr_info);
    return socket_fd;
}
