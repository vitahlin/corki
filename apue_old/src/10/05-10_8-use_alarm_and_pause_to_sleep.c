/**
 * 使用alarm和pause函数来实现sleep进程休眠功能
 *
 * 对比04-10_7-use_alarm_and_pause_to_sleep，避免了alarm和pause的竞争条件。
 * 即使pause从未执行，在发生SIGALRM时，MySleep函数也返回
 *
 * 但是程序也有问题，它涉及与其他信号的交互。如果SIGALRM中断了某个其他信号处理程序，
 * 则调用longjmp会提早终止该信号处理程序。
 */

#include <setjmp.h>

#include "./../lib/apue.h"

static jmp_buf env_alrm;

static void SigAlrm(int);

int MySleep(int seconds) {
    printf("Sleep %d seconds...\n", seconds);

    if (signal(SIGALRM, SigAlrm) == SIG_ERR) {
        return seconds;
    }

    /**
     * setjmp函数直接调用则返回0，若从longjmp调用返回非0值的longjmp中的第二个参数的值
     *
     * setjmp将函数在此处的上下文保存在jmp_buf结构体中，以供longjmp从此结构体恢复
     * 这里避免了04-10_7-use_alarm_and_pause_to_sleep示例中具有的竞争条件，即使pause从未运行，在发生SIGALRM时，MySleep函数也返回
     */
    if (setjmp(env_alrm) == 0) {
        printf("Set alarm\n");
        alarm(seconds);
        pause();
    }

    printf("Alarm end\n");

    // alarm(0)可以取消闹钟，并返回剩余时间
    return alarm(0);
}

int main(int argc, const char** argv) {
    printf("Run begin time %ld\n", time(0));
    MySleep(3);
    printf("Run end time %ld\n", time(0));

    return 0;
}

static void SigAlrm(int sig_num) {
    // 不做任何事情，只是单纯调用触发pause函数
    printf("Run SigAlrm\n");

    // 调用此函数则返回语句setjmp所在的地方
    longjmp(env_alrm, 1);
}