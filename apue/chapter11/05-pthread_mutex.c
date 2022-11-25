/**
 * 线程的互斥锁示例
 */

#include "../lib/apue.h"

int num = 0;

// 互斥锁
pthread_mutex_t mutex;

void* ThreadFunc1(void* arg) {
    printf("Thread 1 start\n");
    int i = 0;
    for (i = 0; i < 3; i++) {
        printf("This is thread 1...\n");

        // 获取互斥锁
        pthread_mutex_lock(&mutex);
        sleep(1);
        num++;
        printf("Thread 1 add one to num %d\n", num);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* ThreadFunc2(void* arg) {
    printf("Thread 2 start\n");
    int i = 0;
    for (i = 0; i < 3; i++) {
        printf("This is thread 2...\n");

        // 获取互斥锁
        pthread_mutex_lock(&mutex);

        /*注意，这里以防线程的抢占，以造成一个线程在另一个线程sleep时多次访问互斥资源，所以sleep要在得到互斥锁后调用*/
        sleep(1);

        num++;

        printf("Thread 2 add one to num %d\n", num);

        // 释放锁
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(int argc, const char** argv) {
    pthread_t tid_1, tid_2;
    int err;
    void* tret;

    // 互斥初始化
    pthread_mutex_init(&mutex, NULL);

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

    printf("End\n");
    return 0;
}