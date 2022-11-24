/**
 * 打印线程ID
 */

#include "../../lib/apue.h"

void PrintIds(const char* s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %u tid %u\n", s, (int)pid, (int)tid);
}

int main(int argc, const char** argv) {
    PrintIds("main thread: ");
    return 0;
}