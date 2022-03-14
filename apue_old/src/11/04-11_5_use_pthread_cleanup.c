/**
 * 线程清理处理程序
 *
 * 在macOS运行出现bus error，书上说明运行结果：
 * thread 1 start
 * thread 1 push complete
 * thread 2 start
 * thread 2 push complete
 * cleanup: thread 2 second handler
 * cleanup: thread 2 first handler
 * thread 1 exit code 1
 * thread 2 exit code 2
 *
 * 两个线程都正确的启动和退出，但是只有线程2的清理处理程序被调用了。
 * 因此如果线程是通过从它的启动例程中返回而终止的化，它的清理处理程序
 * 就不会被调用。同时，清理处理程序是按照与它们安装时相反的顺序被调用。
 */

#include "./../lib/apue.h"

void Cleanup(void* arg) {
    printf("cleanup: %s\n", (char*)arg);
}

void* ThreadFunc1(void* arg) {
    printf("thread 1 start\n");

    char content[25] = "Thread 1 first handler";
    memset(content, '\0', sizeof(content));

    // Todo：修正不能正常打印cleanup xxx的问题
    strcpy(content, "Thread 1 first handler");
    pthread_cleanup_push(Cleanup, content);
    strcpy(content, "Thread 1 second handler");
    pthread_cleanup_push(Cleanup, content);
    printf("thread 1 push complete\n");

    if (arg) {
        return ((void*)1);
    }

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return ((void*)1);
}

void* ThreadFunc2(void* arg) {
    printf("thread 2 start\n");
    char content[25] = "Thread 2 first handler";

    memset(content, '\0', sizeof(content));
    strcpy(content, "Thread 2 first handler");
    pthread_cleanup_push(Cleanup, content);
    strcpy(content, "Thread 2 second handler");
    pthread_cleanup_push(Cleanup, content);
    printf("thread 2 push complete\n");

    if (arg) {
        return ((void*)2);
    }

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)2);
}

int main(int argc, const char** argv) {
    pthread_t tid_1, tid_2;
    int err;
    void* tret;

    // 创建线程1
    err = pthread_create(&tid_1, NULL, ThreadFunc1, (void*)1);
    if (err != 0) {
        ErrorQuit("can not create thread 1");
    }

    // 创建线程2
    err = pthread_create(&tid_2, NULL, ThreadFunc2, (void*)1);
    if (err != 0) {
        ErrorQuit("can not create thread 2");
    }

    err = pthread_join(tid_1, &tret);
    if (err != 0) {
        ErrorQuit("can not join with thread 1");
    }
    printf("thread 1 exit code %ld\n", (long)tret);

    err = pthread_join(tid_2, &tret);
    if (err != 0) {
        ErrorQuit("can not join with thread 2");
    }
    printf("thread 2 exit code %ld\n", (long)tret);

    return 0;
}