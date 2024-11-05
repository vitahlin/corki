#include "ae.h"
#include <stdio.h>
#include <stdlib.h>

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

    return eventLoop;
}