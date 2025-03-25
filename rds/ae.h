
#define AE_READ 1
#define AE_WRITE 2

struct aeEventLoop;

// 事件循环
typedef void aeFileProcess(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask);

typedef void aeBeforeSleepProcessHandler(struct aeEventLoop *eventLoop);

/**
 * 就绪的文件类型
 */
typedef struct aeFiredEvent {
    // 文件描述符
    int fd;
    // 事件类型
    int mask;
} aeFiredEvent;

typedef struct aeFileEvent {
    int aeType;
    aeFileProcess *readFileProc;
    aeFileProcess *writeFileProc;
    void *clientData;
} aeFileEvent;

typedef struct aeEventLoop {
    // 已经注册的事件
    aeFileEvent *events;
    // 已经就绪的事件
    aeFiredEvent *firedEvent;
    int eventCapacity;
    //
    void *apiData;
    aeBeforeSleepProcessHandler *beforeSleepProc;
    aeBeforeSleepProcessHandler *afterSleepProc;
} aeEventLoop;

// 创建事件循环器
aeEventLoop *createEventLoop(int maxSize);
