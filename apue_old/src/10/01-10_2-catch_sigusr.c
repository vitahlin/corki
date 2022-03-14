/**
 * 捕捉SIGUSR1和SIGUSR2信号的示例
 * 使程序在后台运行，终端中输入：./01-10_2-catch_sigusr & ，会打印当前进程ID
 * xxx，然后用kill命令将信号发送给进程，输入：kill -USR1 xxx
 */

#include "./../lib/apue.h"

static void SigUsrHandler(int);

int main(int argc, const char** argv) {
    if (signal(SIGUSR1, SigUsrHandler) == SIG_ERR) {
        ErrorSystem("can not catch SIGUSR1");
    }

    if (signal(SIGUSR2, SigUsrHandler) == SIG_ERR) {
        ErrorSystem("can not catch SIGUSR2");
    }

    for (;;) {
        /**
         * 使进程（或者线程）睡眠状态，直到接收到信号，要么终止，或导致它调用一个信号捕获函数
         */
        pause();
    }

    return 0;
}

static void SigUsrHandler(int sig_num) {
    if (sig_num == SIGUSR1) {
        printf("catch signal SIGUSR1\n");
    } else if (sig_num == SIGUSR2) {
        printf("catch signal SIGUSR2\n");
    } else {
        printf("catch signal %d\n", sig_num);
    }
}