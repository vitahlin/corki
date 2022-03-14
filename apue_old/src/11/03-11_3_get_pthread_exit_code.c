/**
 * 获取已终止的线程的退出码
 */

#include "./../lib/apue.h"

void* ThreadFunc1(void* arg) {
    printf("thread 1 returnning\n");
    return ((void*)1);
}

void* ThreadFunc2(void* arg) {
    printf("thread 2 exiting\n");
    pthread_exit((void*)2);
}

int main(int argc, const char** argv) {
    pthread_t tid_1, tid_2;
    int err;
    void* tret;

    // 创建线程1
    err = pthread_create(&tid_1, NULL, ThreadFunc1, NULL);
    if (err != 0) {
        ErrorQuit("can not create thread 1");
    }

    // 创建线程2
    err = pthread_create(&tid_2, NULL, ThreadFunc2, NULL);
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