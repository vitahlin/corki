/**
 * sigsuspend的另外一种应用：等待一个信号处理程序设置一个全局变量。
 *
 * 示例程序用于捕捉中断和退出信号，但是希望仅当捕捉到退出信号时，才唤醒主例程。
 */

#include "./../lib/apue.h"

volatile sig_atomic_t quit_flag;

static void SigIntFunc(int sig_num) {
    if (sig_num == SIGINT) {
        printf("\ninterrupt\n");
    } else if (sig_num == SIGQUIT) {
        quit_flag = 1;
    }
}

int main(int argc, const char** argv) {
    sigset_t new_mask, old_mask, zero_mask;

    // 设置SIGINT信号的处理
    if (signal(SIGINT, SigIntFunc) == SIG_ERR) {
        ErrorSystem("signal(SIGINT) error");
    }

    // 设置SIGQUIT信号的处理
    if (signal(SIGQUIT, SigIntFunc) == SIG_ERR) {
        ErrorSystem("signal(SIGQUIT) error");
    }

    sigemptyset(&zero_mask);
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGQUIT);

    // 更改信号屏蔽字
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        ErrorSystem("SIG_BLOCK error");
    }

    while (quit_flag == 0) {
        sigsuspend(&zero_mask);
    }

    quit_flag = 0;
    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
        ErrorSystem("SIG_SETMASK error");
    }

    return 0;
}