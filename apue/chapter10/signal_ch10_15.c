/**
 * 进程阻塞SIGQUIT信号，保存了当前信号屏蔽字（以便以后恢复），然后休眠5秒。在此期间所产生的退出信号SIGQUIT都被阻塞，
 * 不递送至该进程，知道该信号不再被屏蔽。在5秒休眠结束后，检查该信号是否是未决都，然后将SIGQUIT设置为不再阻塞。
 * 在设置SIGQUIT为阻塞时，我们保存了老的屏蔽字。为了解除该信号的阻塞，用老的屏蔽字重新设置了进程信号屏蔽字（SIG_SETMASK）。
 * 另一种方法是用SIG_UNBLOCK使阻塞的信号不再阻塞。
 */

#include "../lib/apue.h"

static void SigQuitHandler(int);

int main(int argc, const char** argv) {
    sigset_t new_mask, old_mask, pend_mask;

    if (signal(SIGQUIT, SigQuitHandler) == SIG_ERR) {
        ErrorSystem("can not reset SIGQUIT");
    }

    // 初始化new_mask，信号集里面的所有信号被清空
    sigemptyset(&new_mask);

    // 将SIGQUIT信号加入到new_mask信号集
    sigaddset(&new_mask, SIGQUIT);

    /**
     * 调用sigprocmask可以检测或者更改信号屏蔽字，
     * 如果old_mask是非空指针，那么进程当前的信号屏蔽字通过old_mask返回
     * 如果new_mask是一个指针，第一个参数指示如何修改当前信号屏蔽字
     *
     * SIG_BLOCK 该进程新的信号屏蔽字是其当前信号屏蔽字和new_mask信号集的并集
     */
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        ErrorSystem("SIG_BLOCK error");
    }

    sleep(5);

    /**
     * sigpengding函数返回信号集，其中的各个信号对于调用进程是阻塞的而不能递送，因而也一定是当前未决的
     * 该信号集通过peng_mask参数返回，成功返回0，失败返回-1
     */
    if (sigpending(&pend_mask) < 0) {
        ErrorSystem("sigpending error");
    }

    /**
     * 信号集里面有该信号则返回1，没有则返回0，有错误则返回-1
     */
    if (sigismember(&pend_mask, SIGQUIT)) {
        printf("SIGQUIT pending\n");
    }

    /**
     * SIG_SETMASK 将old_mask信号集设置为信号掩码
     */
    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
        ErrorSystem("SIG_SETMASK error");
    }

    printf("SIGQUIT unblocked\n");
    sleep(5);

    return 0;
}

static void SigQuitHandler(int sig_num) {
    printf("catch SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        ErrorSystem("can not reset SIGQUIT");
    }
}