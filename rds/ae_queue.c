#include "ae.h"
#include "zmalloc.h"
#include <sys/event.h>
#include "log.h"

/**
 * 1. 如果要创建对应的apiData，是不是要有一个对应平台的结构体apiData
 * 2. 这里需要了解Kqueue & Kevent的原理和使用
 */

typedef struct aeApiData{
    int kqfd;
    struct kevent *event;
    int *event_mask;
} aeApiData;

static int aeApiCreate(aeEventLoop *eventLoop){
    aeApiData *state = zmalloc(sizeof(aeApiData));
    if (NULL == state) {
        loggerError("aeApiData分配内存失败");
        return -1;
    }

    state->event = zmalloc(sizeof(struct kevent) * eventLoop->eventCapacity);
    if (NULL == state->event) {
        loggerError("aeApiData event分配内存失败");
        return -1;
    }

    state->kqfd = kqueue();
    if (state->kqfd == -1) {
        loggerError("aeApiData kqfd失败");
        return -1;
    }

    state->event_mask = zmalloc(sizeof(size_t) * eventLoop->eventCapacity);
    if (state->event_mask == NULL) {
        return -1;
    }

    return 0;
}