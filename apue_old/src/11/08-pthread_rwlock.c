
/**
 * 读写锁的使用
 */

#include "./../lib/apue.h"

pthread_rwlock_t rwlock;
int count = 0;

void* ReadFunc(void* ptr) {
    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("Thread %x read, count %d\n", (int)pthread_self(), count);
        pthread_rwlock_unlock(&rwlock);

        sleep(1);
    }

    pthread_exit(NULL);
}

void* WriteFunc(void* ptr) {
    while (1) {
        pthread_rwlock_wrlock(&rwlock);
        count++;
        printf("Thread %x write, count %d\n", (int)pthread_self(), count);
        pthread_rwlock_unlock(&rwlock);

        sleep(1);
    }

    pthread_exit(NULL);
}

int main(int argc, const char** argv) {
    pthread_t tid[5];
    int i;

    pthread_rwlock_init(&rwlock, NULL);

    // 开启两个读线程
    for (i = 0; i < 2; i++) {
        pthread_create(&tid[i], NULL, ReadFunc, NULL);
    }

    // 开启3个写线程
    for (i = 2; i < 5; i++) {
        pthread_create(&tid[i], NULL, WriteFunc, NULL);
    }

    for (i = 0; i < 5; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
