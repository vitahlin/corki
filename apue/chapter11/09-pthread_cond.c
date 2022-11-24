
/**
 * 线程条件变量的使用，2个线程对count每次分别加1，第三个线程等count大于10后一次加100
 */

#include "../../lib/apue.h"

#define NUM_THREADS 3
#define TOTAL_COUNT 10
#define COUNT_LIMIT 10

int count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold;
int thread_ids[3] = {0, 1, 2};

void* IncreaseCount(void* pthread_id) {
    int task_id = 0;
    int* my_id = (int*)pthread_id;

    for (int i = 0; i < TOTAL_COUNT; i++) {
        pthread_mutex_lock(&count_mutex);
        task_id = count;
        count++;

        /**
         * 唤醒一个阻塞在该条件变量的线程
         * 如果没有线程被阻塞在条件变量上，那么调用此函数没有作用
         */
        pthread_cond_signal(&count_threshold);

        printf("Increase count(): thread %d, count=%d, unlocking mutex\n",
               *my_id, count);

        pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }

    printf("Increase count(): thread %d, thresold reached\n", *my_id);

    pthread_exit(NULL);
}

void* WatchCount(void* idp) {
    int* my_id = (int*)idp;
    printf("Start WatchCount(): thread %d\n", *my_id);

    pthread_mutex_lock(&count_mutex);
    while (count < COUNT_LIMIT) {
        sleep(1);

        /**
         * 函数将自动解锁count_mutex互斥锁，并使当前的线程阻塞在count_threshold条件变量上，
         * 被阻塞的线程可以被pthread_cond_signal、pthread_cond_broadcast函数唤醒，
         * 也可能在被信号中断后唤醒，pthread_cond_wait函数的返回并不意味着条件的值一定发生了变化，
         * 必须重新检查条件的值。
         *
         * 本例子中的线程被唤醒后，仍然在while中判断COUNT_LIMIT是否满足条件值。
         * pthread_cond_wait函数返回时，相应的互斥锁将被当前线程锁定，即使函数是出错返回
         */
        pthread_cond_wait(&count_threshold, &count_mutex);
        printf("WatchCount(): thread %d condition signal received\n", *my_id);
    }

    count += 100;
    pthread_mutex_unlock(&count_mutex);

    pthread_exit(NULL);
}

int main(int argc, const char** argv) {
    pthread_t threads[3];
    int i;

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_threshold, NULL);

    for (i = 0; i < NUM_THREADS - 1; i++) {
        pthread_create(&threads[i], NULL, IncreaseCount, (void*)&thread_ids[i]);
    }
    pthread_create(&threads[NUM_THREADS - 1], NULL, WatchCount,
                   (void*)&thread_ids[NUM_THREADS - 1]);

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main(): Waited on %d threads. Done.\n", NUM_THREADS);

    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold);

    return 0;
}
