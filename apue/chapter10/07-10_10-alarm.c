/**
 * 程序中有一个读低速设备可能阻塞的操作，我们希望超过一定时间量后就停止执行。就可以使用alarm来对操作设置时间上限值。
 *
 * 运行结果：
 * 在macOS上运行，时间超过后并不会中断输入，而是一直等到输入完成，与书中说明结果不符合。
 *
 * 程序有两个问题：
 * 1.
 * 第一次alarm调用和read调用之间有一个竞争条件。如果内核在这两个函数调用之间使进程阻塞，不能占用处理机运行，
 * 而其时间长度又超过闹钟时间，则read可能永远阻塞。大多数这种类型的操作使用较长的闹钟时间，例如1分钟或者更长一点，
 * 使这种问题不会发生，但无论如何这是一个竞争条件
 * 2.
 * 如果系统调用是自动重启动的，则当从SIGALRM信号处理程序返回时，read并不被中断，这种情况下，设置时间限制不起作用。
 */

#include "../../lib/apue.h"

static void SigAlrm(int sig_num) {}

int main(int argc, const char** argv) {
    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, SigAlrm) == SIG_ERR) {
        ErrorSystem("signal(SIGALRM) error");
    }

    alarm(10);
    printf("begin input:\n");

    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
        ErrorSystem("read error");
    }

    alarm(0);

    write(STDOUT_FILENO, line, n);

    return 0;
}