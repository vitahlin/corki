/**
 * 解决进程的竞争条件，子进程先运行
 */

#include "../lib/apue.h"

static void output(char *str) {
    char *ptr;
    int c;

    // 取消输出缓存
    setbuf(stdout, NULL);

    for (ptr = str; (c = *ptr++) != 0;) {
        putc(c, stdout);
    }
}

int main(int argc, const char **argv) {
    pid_t pid;

    TELL_WAIT();

    char child_str[] = "output from child\n";
    char parent_str[] = "output from parent\n";

    if ((pid = fork()) < 0) {
        ErrorQuit("fork error");
    } else if (pid == 0) {
        output(child_str);
        TELL_PARENT(getppid());
    } else {
        WAIT_CHILD();
        output(parent_str);
    }

    return 0;
}
