/**
 * 使用alarm和pause函数来实现sleep进程休眠功能
 *
 * 但是这种简单实现有3个问题：
 * 1.
 * 如果在调用MySleep之前，已经设置了闹钟，则它被MySleep中的第一次alarm调用擦除。
 * 可用下列方法更正：检查第一次调用alarm的返回值，如果值小于本次调用alarm的参数值，则只应等到已有的闹钟超时。
 * 如果之前奢姿的闹钟超时时间晚于本次设置值，则在MySleep函数返回之前，重置此闹钟，使其在之前闹钟的设定时间再次发生超时
 * 2.
 * 程序修改了对SIGALRM的配置。如果编写了一个函数供其他函数调用，则在该函数被调用时要先保存原配置，在该函数返回前再恢复原配置。
 * 更正这一点的方法是：保存signal函数的返回值，在返回前重置原配置。
 * 3.
 * 第一次调用alarm和pause之间有一个竞争条件。在一个繁忙的系统中，可能alarm在调用pause之前超时，并调用了信号处理程序。
 * 如果发生了这种情况，则在调用pause后，如果没有捕捉到其他信号，调用者将被永远挂起。
 */

#include "../../lib/apue.h"

static void SigAlrm(int);

int MySleep(int seconds) {
    printf("Sleep %d seconds...\n", seconds);

    if (signal(SIGALRM, SigAlrm) == SIG_ERR) {
        return seconds;
    }

    printf("Set alarm\n");
    alarm(seconds);

    /**
     * pause()函数使调用进程挂起直至捕捉到一个信号
     * 只有执行了一个信号处理程序并从其返回时，pause才返回，在这种情况下，pause返回-1，error设置为EINTR
     */
    pause();

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
    printf("Run SigAlarm...\n");
}