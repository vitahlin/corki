#include <stdio.h>
#include <sys/types.h>

#define AE_READ 1
#define AE_WRITE 2


// 客户端数据和服务端数据
typedef struct rdsClient {
} rdsClient;

struct rdsServer {
    // pid_t 用于定义进程ID
    pid_t pid;
    int32_t clientNum;
    rdsClient *clients;
    int maxClientCount;
};

// 事件循环
typedef void aeFileProcess(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask);

typedef struct aeFileEvent {
    int aeType;
    aeFileProcess *readFileProc;
    aeFileProcess *writeFileProc;
    void *clientData;
} aeFileEvent;

typedef struct aeEventLoop {
    aeFileEvent *events;
    int eventCapacity;
    void *apiData;
} aeEventLoop;