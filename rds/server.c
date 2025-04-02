#include <stdlib.h>

#include "server.h"
#include "log.h"
#include "anet.h"

struct rdsServer server;


/**
 * 初始化服务器配置
 */
void initServerConfig() {
}

int listenToPort(int serverPort, socketFds *fds) {
    int socket_fd = -1;
    socket_fd = anetTcpServer(server.net_err, serverPort, NULL, server.tcp_backlog);
    if (socket_fd < 0) {

    }
}

int main(int argc, char **argv) {
    printf("Hello this is my toy redis.\n");

    initServerConfig();

    // 创建事件循环器
    server.eventLoop = createEventLoop(10);
    if (server.eventLoop == NULL) {
        exit(1);
    }

    if (listenToPort(6379, &server.tcpFds) == RDS_ERROR) {
        loggerError("listenToPort failed");
        exit(1);
    }

    return 0;
}

