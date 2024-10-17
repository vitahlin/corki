#include <stdlib.h>
#include "server.h"

/**
 * 初始化服务器配置
 */
void initServerConfig() {
}

int main(int argc, char **argv) {
    printf("Hello this is my toy redis");

    initServerConfig();

    return 0;
}

aeEventLoop *createEventLoop(int capacity) {
    aeEventLoop *eventLoop;

    eventLoop = malloc(sizeof(*eventLoop));
    if (eventLoop == NULL) {
        return NULL;
    }

    eventLoop->eventCapacity = capacity;

    eventLoop->events = malloc(sizeof(aeFileEvent) * capacity);
    if (eventLoop->events == NULL) {
        return NULL;
    }

    return eventLoop;
}