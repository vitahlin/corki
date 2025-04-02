#include <stdio.h>
#include <stdlib.h>
#include "ae_queue.c"

aeEventLoop *createEventLoop(int maxSize) {
    aeEventLoop *eventLoop;
    eventLoop = malloc(sizeof(*eventLoop));
    eventLoop->events = malloc(sizeof(aeFileEvent) * maxSize);
    eventLoop->firedEvent = malloc(sizeof(aeFiredEvent) * maxSize);
    eventLoop->eventCapacity = maxSize;
    eventLoop->beforeSleepProc = NULL;
    eventLoop->afterSleepProc = NULL;

    printf("create eventLoop success\n");
    // 根据不同的系统创建不同的多路复用函数，目前mac直接实现kqueue
    if (aeApiCreate(eventLoop) == -1) {
        loggerError("aeApiCreate失败");
        return NULL;
    }

    // 初始化开始的各个事件类型为空
    for (int i = 0; i < eventLoop->eventCapacity; i++) {
        eventLoop->events[i].aeType = AE_TYPE_NONE;
    }

    return eventLoop;
}