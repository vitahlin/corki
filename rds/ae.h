#define AE_TYPE_NONE 0
#define AE_TYPE_READ 1
#define AE_TYPE_WRITE 2


typedef void aeFileProcess(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask);

typedef struct aeFileEvent {
    int aeType;
    aeFileProcess *readFileProc;
    aeFileProcess *writeFileProc;
    void *client_data;
} aeFileEvent;

typedef struct aeFiredEvent {
    int fd;
    int mask;
} aeFiredEvent;

typedef struct aeEventLoop {
    int max_fx;
} aeEventLoop;
