#include <stdlib.h>

#include "server.h"
#include "log.h"

struct rdsServer server;

/**
 * 初始化服务器配置
 */
void initServerConfig() {
}

int listenToPort(int serverPort, socketFds *fds) {
    
    return 0;
}

int main(int argc, char **argv) {
    printf("Hello this is my toy redis.\n");

    initServerConfig();

    // 创建事件循环器
    server.eventLoop = createEventLoop(10);
    if (server.eventLoop == NULL) {
        exit(1);
    }

    if (listenToPort(6379, &server.tcpFds) == -1) {
        exit(1);
    }

    return 0;
}

