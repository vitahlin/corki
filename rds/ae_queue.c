#include "ae.h"


/**
 * 1. 如果要创建对应的apiData，是不是要有一个对应平台的结构体apiData
 * 2. 这里需要了解Kqueue & Kevent的原理和使用
 */

typedef struct aeApiData{
    int kqfd;
    struct kevent *event;

};

static int aeApiCreate(aeEventLoop *eventLoop){


    return 0;
}