/**
 * 使用alarm和pause函数来实现sleep进程休眠功能
 *
 * 运行时执行Ctrl+C来中断程序，会发现MySleep函数引起的longjmp会使另外一个信号处理程序SigIntHandler提早终止，即使它还未完成。
 */

#include <setjmp.h>

#include "../lib/apue.h"

static jmp_buf env_alrm;

static void SigIntHandler(int);
static void SigAlrm(int);

int MySleep(int seconds) {
    printf("Sleep %d seconds...\n", seconds);

    if (signal(SIGALRM, SigAlrm) == SIG_ERR) {
        return seconds;
    }

    if (setjmp(env_alrm) == 0) {
        printf("Set alarm\n");
        alarm(seconds);
        pause();
    }

    printf("Alarm end\n");

    return alarm(0);
}

int main(int argc, const char** argv) {
    unsigned int unslept;

    /**
     * SIGINT程序终止信号
     */
    if (signal(SIGINT, SigIntHandler)) {
        ErrorSystem("signal(SIGINT) error");
    }

    printf("Run begin time %ld\n", time(0));
    MySleep(5);
    printf("Run end time %ld\n", time(0));

    printf("MySleep returned: %d\n", unslept);

    return 0;
}

static void SigIntHandler(int sig_num) {
    printf("SigInt start\n");

    int i, j;

    // 用volatile阻止优化编译程序去除循环语句
    volatile int k;

    printf("Int handler begin time %ld\n", time(0));

    // 让循环的运行时间大于休眠时间
    for (i = 0; i < 300000; i++) {
        for (j = 0; j < 40000; j++) {
            k += i * j;
        }
    }

    printf("int handler end time %ld\n", time(0));
    printf("SigInt end\n");
}

static void SigAlrm(int sig_num) {
    printf("Run SigAlrm...\n");
    longjmp(env_alrm, 1);
}