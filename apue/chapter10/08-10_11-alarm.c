/**
 * 程序中有一个读低速设备可能阻塞的操作，我们希望超过一定时间量后就停止执行。就可以使用alarm来对操作设置时间上限值。
 *
 * 和07-10_10-alarm程序的区别在于，无论系统是否重新启动被中断的系统调用，该程序都会如预期那样工作。等待输入超过一定时间量后就停止运行。
 */

#include <setjmp.h>

#include "../../lib/apue.h"

static jmp_buf env_alrm;

static void SigAlrm(int);

int main(int argc, const char** argv) {
    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, SigAlrm) == SIG_ERR) {
        ErrorSystem("signal(SIGALRM) error");
    }

    if (setjmp(env_alrm) != 0) {
        ErrorQuit("read timeout");
    }

    alarm(10);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0) {
        ErrorSystem("read error");
    }

    alarm(0);

    write(STDOUT_FILENO, line, n);

    return 0;
}

static void SigAlrm(int sig_num) {
    longjmp(env_alrm, 1);
}