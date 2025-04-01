
#include "anet.h"

static int anetTcpServer(char *err, int port, char *bindaddr, int backlog) {
    struct addrinfo hint, *p, *serv_addr_info;

    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    hint.ai_flags = AI_PASSIVE;

    return 0;
}
