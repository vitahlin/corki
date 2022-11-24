#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include "./apue.h"

/**
 * volatile是一个类型修饰符，确保本条执行不会因为编译器优化而忽略，且要求每次直接读值
 * sig_atomic_t可以认为就是int类型，能保证操作是原子的
 */
static volatile sig_atomic_t sigflag;

static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) {
    sigflag = 1;
}

void TELL_WAIT() {
    /**
     * SIGUSER1和SIGUSER2是用户自定义信号
     */
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        ErrorQuit("signal sigusr1 error");
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        ErrorQuit("signal sigusr2 error");
    }

    // 将newmask信号集初始化为空，执行成功返回0，有错误返回-1
    sigemptyset(&newmask);
    sigemptyset(&zeromask);

    // 将参数SIGUSR1代表的信号加入至参数&newmark信号集里
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /**
     * 调用该函数的进程，使用新的信号屏蔽集。newmask是我们希望阻塞的附加信号集
     */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        ErrorQuit("SIG_BLOCK error");
    }
}

void WAIT_PARENT() {
    while (sigflag == 0) {
        /**
         * sigsuspend用于在接收某个信号之前，临时用参数zeromask替换进程的信号掩码，并暂停进程执行，直到收到信号为止
         */
        sigsuspend(&zeromask);
    }

    sigflag = 0;

    /**
     * SIG_SETMASK代表该进程新的信号屏蔽字将被oldmask信号集替代
     */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        ErrorQuit("SIG_SETMASK error");
    }
}

void WAIT_CHILD() {
    while (sigflag == 0) {
        sigsuspend(&zeromask);
    }

    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        ErrorQuit("SIG_SETMASK error");
    }
}

void TELL_CHILD(pid_t pid) {
    kill(pid, SIGUSR1);
}

void TELL_PARENT(pid_t pid) {
    kill(pid, SIGUSR1);
}