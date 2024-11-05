#include <stdlib.h>

#include "server.h"

struct rdsServer server;

/**
 * 初始化服务器配置
 */
void initServerConfig() {
}

int main(int argc, char **argv) {
    printf("Hello this is my toy redis.\n");

    initServerConfig();

    server.eventLoop = createEventLoop(10);

    return 0;
}