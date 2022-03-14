/**
 * 程序演示了信号处理程序被调用时，系统所设置的信号屏蔽字如何自动地包括刚被捕捉到的信号。
 * 此程序也示例说明了如何使用sigsetjmp和siglongjmp函数。
 * 此例中：当调用一个信号处理程序时，被捕捉到的信号加到进程的当前信号屏蔽字中。
 * 当从信号处理程序返回时，恢复原来的屏蔽字。
 *
 * 运行过程：
 * 1.
 * 输入：./10-10_20-signal &
 * 输出：
 * [1] 1097
 * starting main:
 *
 * 2.
 * 给1097进程发送USR1信号
 * 输入：kill -USR1 1097
 * 输出：
 * start SigUsr1:  SIGUSR1
 * in SigAlrm:  SIGUSR1 SIGALRM
 * finish SigUsr1:  SIGUSR1
 * ending main:
 *
 * 3. 键入回车
 * 输出：
 * [1]+  Done                    ./10-10_20-signal
 */

#include <setjmp.h>
#include <time.h>

#include "./../lib/apue.h"

void PrintMask(const char* str);

static void SigUsr1(int);
static void SigAlrm(int);
static jmp_buf jmp_buff;
static volatile sig_atomic_t can_jump;

int main(int argc, const char** argv) {
    if (signal(SIGUSR1, SigUsr1) == SIG_ERR) {
        ErrorSystem("signal(SIGUSR1) error");
    }

    if (signal(SIGALRM, SigAlrm) == SIG_ERR) {
        ErrorSystem("signal(SIGALRM) error");
    }

    PrintMask("starting main: ");

    if (sigsetjmp(jmp_buff, 1)) {
        PrintMask("ending main: ");
        exit(0);
    }

    can_jump = 1;
    for (;;) {
        pause();
    }

    return 0;
}

static void SigAlrm(int sig_num) {
    printf("catch alarm signal, time: %ld\n", time(0));
    PrintMask("in SigAlrm: ");
}

static void SigUsr1(int sig_num) {
    time_t start_time;

    if (can_jump == 0) {
        return;
    }

    PrintMask("start SigUsr1: ");

    printf("start alarm, time: %ld\n", time(0));
    alarm(3);
    start_time = time(NULL);

    for (;;) {
        if (time(NULL) > start_time + 5) {
            break;
        }
    }

    PrintMask("finish SigUsr1: ");

    can_jump = 0;

    siglongjmp(jmp_buff, 1);
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
            printf("SIGINT");
        }

        if (sigismember(&sigset, SIGQUIT)) {
            printf("SIGQUIT");
        }

        if (sigismember(&sigset, SIGUSR1)) {
            printf("SIGUSR1");
        }

        if (sigismember(&sigset, SIGALRM)) {
            printf("SIGALRM");
        }

        printf("\n");
    }

    errno = errno_save;
}