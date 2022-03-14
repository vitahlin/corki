/**
 * 打印线程ID
 */

#include "./../lib/apue.h"

void PrintIds(const char* s) {
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    /**
     * 新线程是通过调用pthread_self函数获取自己的ID，而不是从共享内存中读出
     * 或者从线程的启动例程中以参数的形式收到。
     * pthread_create函数会通过第一个参数返回新建线程的ID。在本例中，主线程
     * 把新线程ID存放在new_tid中，但是新建的线程并不能安全地使用它，如果新线程
     * 在主线程调用pthread_create返回之前就运行了，那么新线程看到的是未经初始
     * 化的new_tid的内容，这个内容并不是正确的线程ID
     */
    tid = pthread_self();
    printf("%s pid %d tid %d\n", s, (int)pid, (int)tid);
}

void* ThreadFunc(void* arg) {
    PrintIds(" new thread: ");
    return ((void*)0);
}

int main(int argc, const char** argv) {
    pthread_t new_tid;

    int err = pthread_create(&new_tid, NULL, ThreadFunc, NULL);
    if (err != 0) {
        ErrorQuit("can not create thread: %s\n", strerror(err));
    }

    PrintIds("main thread: ");

    // 主线程需要休眠，如果不休眠，它就可能退出，这样在新进程有机会运行之前整个进程可能就已经终止
    sleep(1);

    return 0;
}