/**
 * pthread_mutex_timedlock 用法
 */

#include "../lib/apue.h"

int main(int argc, const char** argv) {
    int err;

    struct timespec tout;
    struct tm* tmp;

    char buf[64];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mutex);
    printf("Mutex is locked\n");

    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("Current time is %s\n", buf);

    tout.tv_sec += 10;

#ifndef __APPLE__
    err = pthread_mutex_timedlock(&mutex, &tout);
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("The time is now %s\n", buf);
    if (err == 0) {
        printf("Mutex locked again\n");
    } else {
        printf("Can not lock mutex again: %s\n", strerror(err));
    }
#else
    printf("pthread_mutex_timedlock is not supported on macOS\n");
#endif

    return 0;
}