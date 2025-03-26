#include <stdio.h>
#include <sys/types.h>
#include "ae.h"


// 客户端数据和服务端数据
typedef struct rdsClient {
} rdsClient;

struct rdsServer {
    // pid_t 用于定义进程ID
    pid_t pid;
    int32_t clientNum;
    rdsClient *clients;

    // 定义结构保存服务端socket数据
    
    int maxClientCount;
    aeEventLoop *eventLoop;
};

extern struct rdsServer server;
