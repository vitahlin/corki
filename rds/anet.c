
#include "anet.h"
#include "server.h"
#include "log.h"
#include <string.h>


int anetTcpServer(char *err, int port, char *bindaddr, int backlog) {
    struct addrinfo hint, *p, *serv_addr_info;
    int status, s = -1;
    char _port[6];
    snprintf(_port, 6, "%d", port);
    int fd;

    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, _port, &hint, &serv_addr_info)) != 0) {
        logger(LOG_ERROR, gai_strerror(status));
        return RDS_ERROR;
    }

    for (p = serv_addr_info; p != NULL; p = p->ai_next) {
        if ((s = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            logger(LOG_ERROR, "socket: %s", strerror(s));
            continue;
        }

        if (bind(s, p->ai_addr, p->ai_addrlen) == 0) {
            freeaddrinfo(serv_addr_info);
            return fd;
        }
    }

    return 0;
}
