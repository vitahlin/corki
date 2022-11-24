
/**
 * 读写锁的使用
 */

#include "../../lib/apue.h"

struct {
    pthread_rwlock_t rwlock;
    int product;
} sharedData = {PTHREAD_RWLOCK_INITIALIZER, 0};

void* Procude(void* ptr) {
    for (int i = 0; i < 5; ++i) {
        pthread_rwlock_wrlock(&sharedData.rwlock);
        sharedData.product = i;
        printf("Produce: %d\n", i);
        pthread_rwlock_unlock(&sharedData.rwlock);

        sleep(1);
    }

    pthread_exit(NULL);
}

void* ConsumeOne(void* ptr) {
    for (int i = 0; i < 5;) {
        pthread_rwlock_rdlock(&sharedData.rwlock);
        printf("ConsumeOne: %d\n", sharedData.product);
        pthread_rwlock_unlock(&sharedData.rwlock);

        ++i;
        sleep(1);
    }

    pthread_exit(NULL);
}

void* ConsumeTwo(void* ptr) {
    for (int i = 0; i < 5;) {
        pthread_rwlock_rdlock(&sharedData.rwlock);
        printf("ConsumeTwo: %d\n", sharedData.product);
        pthread_rwlock_unlock(&sharedData.rwlock);

        ++i;
        sleep(1);
    }

    pthread_exit(NULL);
}

int main(int argc, const char** argv) {
    pthread_t tid1, tid2, tid3;

    pthread_create(&tid1, NULL, Procude, NULL);
    pthread_create(&tid2, NULL, ConsumeOne, NULL);
    pthread_create(&tid3, NULL, ConsumeTwo, NULL);

    void* tret;

    pthread_join(tid1, &tret);
    pthread_join(tid2, &tret);
    pthread_join(tid3, &tret);

    return 0;
}
