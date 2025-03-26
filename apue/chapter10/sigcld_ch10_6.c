/**
 * 父进程在fork之前先注册了SIGCLD的信号处理函数SigcldHandler,然后做自己的事情。
 * 当子进程退出时，会给父进程发送一个SIGCLD信号。然后SigcldHandler函数就会执行。
 *
 * 可以在SigcldHandler函数中调用wait获得子进程退出时的状态，并且此时wait不会阻塞。
 * 当SigcldHandler函数执行完后，父进程又继续做自己的事情。
 */

#include "../lib/apue.h"

static void SigcldHandler(int);

int main(int argc, const char** argv) {
    pid_t pid;

    if (signal(SIGCLD, SigcldHandler) == SIG_ERR) {
        printf("signal error\n");
    }

    if ((pid = fork()) < 0) {
        printf("fork error\n");
    } else if (pid == 0) {
        sleep(2);
        _exit(0);
    }

    pause();
    exit(0);

    return 0;
}

static void SigcldHandler(int sig_num) {
    pid_t pid;
    int status;

    printf("SIGCLD received\n");

    if (signal(SIGCLD, SigcldHandler) == SIG_ERR) {
        printf("signal error\n");
    }

    if ((pid = wait(&status)) < 0) {
        printf("wait error\n");
    }

    printf("pid=%d\n", pid);
}