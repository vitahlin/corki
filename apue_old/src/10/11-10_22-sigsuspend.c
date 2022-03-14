/**
 * 更改进程的信号屏蔽字可以阻塞所选择的信号，或解除对它们的阻塞。使用这种技术可以保护不希望由信号中断的代码临界区。
 * 如果希望对一个信号解除阻塞，然后pause以等待以前被阻塞的信号发生，则又将如何呢？
 * 错误方式的示例代码：
 * sigemptyset(&new_mask);
 * sigaddset(&new_mask, SIGINT);
 * if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
 *     ErrorSystem("SIG_BLOCK error");
 *  }
 *  if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
 *      ErrorSystem("SIG_MASK error");
 *  }
 *   pause();
 *
 * 如果在阻塞时，产生了信号，那么该信号的传递就被推迟直到对它解除了阻塞。对应用程序而言，该信号发生了在解除对SIGINT的阻塞
 * 和pause之间（取决于内核如何实现信号）。如果发生了这种情况，或者如果在解除阻塞时刻和pause之间确实发生了信号，那么就会
 * 产生问题。因为可能不会再见到该信号，在这个时间窗口中发生的信号丢失了。这样就使pause永远阻塞。
 *
 * 为了纠正这个问题，需要在一个原子操作中先恢复信号屏蔽字，然后使进程休眠。这个功能是由sigsuspend函数提供。
 *
 * sigsuspend的用法，保护代码临界区，使其不被特定信号中断
 */

#include "./../lib/apue.h"

void PrintMask(const char* str);
static void SigInt(int);
static void SigUsr1(int);

int main(int argc, const char** argv) {
    sigset_t new_mask, old_mask, wait_mask;

    PrintMask("program start:");

    // 捕捉SIGINT信号
    if (signal(SIGINT, SigInt) == SIG_ERR) {
        ErrorSystem("signal(SIGINT) error");
    }

    // 捕捉SIGINT信号
    if (signal(SIGUSR1, SigUsr1) == SIG_ERR) {
        ErrorSystem("signal(SIGUSR) error");
    }

    sigemptyset(&wait_mask);
    sigaddset(&wait_mask, SIGUSR1);
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);

    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        ErrorSystem("SIG_BLOCK error");
    }
    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
        ErrorSystem("SIG_MASK error");
    }
    pause();

    // 将SIGINT信号阻塞，同时保存当前信号集
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        ErrorSystem("SIG_BLOCK error");
    }

    PrintMask(" in critical region: ");

    /**
     * 临界区代码执行
     */

    /**
     * sigsuspend的原子操作是：
     * 1.设置新的mask阻塞当前进程，这里是用wait替换new，即阻塞SIGUSR1信号
     * 2.收到SIGUSR1信号，阻塞，程序继续挂起；收到其他信号，恢复原先的mask
     * 3.调用该进程设置的信号处理函数（程序中如果先来SIGUSR1信号，然后过来SIGINT信号，则信号处理函数会调用两次，第一次执行SigInt，第二次执行SigUsr1，因为SigUsr1是前面阻塞的）
     * 4.待信号处理函数返回，sigsuspend返回了（sigsuspend将捕捉信号和信号处理函数集成到一起了）
     *
     * sigsuspend实际是将sigprocmask和pause结合起来原子操作，sigsuspend返回时，将信号屏蔽字恢复为调用它之前的值
     */
    if (sigsuspend(&wait_mask) != -1) {
        ErrorSystem("sigsuspend error");
    }

    PrintMask("after return from sigsuspend: ");

    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
        ErrorSystem("SIG_MASK error");
    }

    PrintMask("program exit: ");

    return 0;
}

// 信号处理函数的实现
static void SigInt(int sig_num) {
    PrintMask("\nin sig_int: ");
}

static void SigUsr1(int sig_num) {
    printf("catch SIGUSR1\n");
}

void PrintMask(const char* str) {
    sigset_t sigset;
    int errno_save;

    errno_save = errno;

    if (sigprocmask(0, NULL, &sigset) < 0) {
        ErrorReturn("sigprocmask error");
    } else {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT)) {
            printf(" SIGINT");
        }

        if (sigismember(&sigset, SIGQUIT)) {
            printf(" SIGQUIT");
        }

        if (sigismember(&sigset, SIGUSR1)) {
            printf(" SIGUSR1");
        }

        if (sigismember(&sigset, SIGALRM)) {
            printf(" SIGALRM");
        }

        printf("\n");
    }

    errno = errno_save;
}