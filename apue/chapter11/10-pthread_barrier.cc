
/**
 * 线程屏障的使用，使用8个线程分解800万个数的排序工作
 * Todo：macOS编译不通过
 */

#include "../../lib/apue.h"

#define NTHR 8
#define NUMBER 8000000L
#define TNUM (NUMBER / NTHR)

long nums[NUMBER];
long sum_nums[NUMBER];

pthread_barrier_t b;

#ifdef SOLARIS
#define heapsort qsort
#else
extern int heapsort(void*, size_t, size_t, int (*)(const void*, const void*));
#endif

int CompareLong(const void* arg_1, const void* arg_2) {
    long l_1 = *(long*)arg_1;
    long l_2 = *(long*)arg_2;

    if (l_1 == l_2) {
        return 0;
    } else if (l_1 < l_2) {
        return -1;
    } else {
        return 1;
    }
}

void* ThreadFunc(void* arg) {
    long idx = (long)arg;

    heapsort(&nums[idx], TNUM, sizeof(long), CompareLong);

    pthread_barrier_wait(&b);

    return ((void*)0);
}

void merge() {
    long idx[NTHR];
    long i, minidx, sidx, num;

    for (i = 0; i < NTHR; i++) {
        idx[i] = i * TNUM;
    }

    for (sidx = 0; sidx < NUMBER; sidx++) {
        num = LONG_MAX;
        for (i = 0; i < NTHR; i++) {
            if ((idx[i] < (i + 1) * TNUM && (nums[idx[i]] < num))) {
                num = nums[idx[i]];
                minidx = 1;
            }

            sum_nums[sidx] = nums[idx[minidx]];
            idx[minidx]++;
        }
    }
}

int main(int argc, const char** argv) {
    long i;
    struct timeval start, end;
    long long start_usec, end_usec;
    double elapsed;
    int err;
    pthread_t tid;

    srandom(1);
    for (i = 0; i < NUMBER; i++) {
        nums[i] = random();
    }

    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR + 1);

    for (i = 0; i < NTHR; i++) {
        err = pthread_create(&tid, NULL, ThreadFunc, (void*)(i * TNUM));
        if (err != 0) {
            ErrorQuit("can not create thread");
        }
    }

    pthread_barrier_wait(&b);
    merge();

    gettimeofday(&end, NULL);

    start_usec = start.tv_sec * 1000000 + start.tv_usec;
    end_usec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(end_usec - start_usec) / 1000000.0;
    printf("sort took %.4f seconds\n", elapsed);

    for (i = 0; i < NUMBER; i++) {
        printf("%ld\n", sum_nums[i]);
    }

    return 0;
}
