/**
 * 通过信号相关函数实现abort功能
 *
 * ISO
 * C规定，调用abort将向主机环境递送一个未成功终止的通知，其方法是调用raise(SIGABRT)函数。
 *
 * ISO C要求若捕捉到此信号而且相应信号处理程序返回，abort仍不会返回到其调用者。
 * 如果捕捉到此信号，则信号处理程序不能返回的唯一方法是它调用exit、_exit、_Exist、longjmp、或siglongjmp。
 *
 * 让进程捕捉SIGABRT的意图是：在进程终止之前由其执行所需的清理操作。如果进程并不在信号处理程序中终止自己，
 * POSIX.1声明当信号处理程序返回时，abort终止该进程。
 */

#include "../lib/apue.h"

void MyAbort(void) {
    sigset_t mask;
    struct sigaction action;

    sigaction(SIGABRT, NULL, &action);

    if (action.sa_handler == SIG_IGN) {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }

    if (action.sa_handler == SIG_DFL) {
        fflush(NULL);
    }

    sigfillset(&mask);
    sigdelset(&mask, SIGABRT);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    kill(getpid(), SIGABRT);

    fflush(NULL);
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    exit(1);
}

int main(int argc, const char** argv) {
    printf("running main...\n");
    MyAbort();
    return 0;
}