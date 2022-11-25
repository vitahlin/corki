/**
 * fork函数，子进程对变量所做的改变并不影响父进程该变量的值
 */

#include "../lib/apue.h"

int global_var = 6;
char buf[] = "A write to stdout\n";

int main(int argc, const char **argv) {
    int var = 88;
    pid_t pid;

    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        ErrorQuit("write error");
    }

    printf("before fork, var=%d\n", var);

    if ((pid = fork()) < 0) {
        ErrorQuit("fork error");
    } else if (pid == 0) {
        // child
        global_var++;
        var++;
    } else {
        // fork之后，父进程先执行还是子进程先执行是不确定的，这里让父进程休眠2秒以让子进程先执行
        sleep(2);
    }

    printf("pid=%d, global var=%d, var=%d\n", getpid(), global_var, var);
    return 0;
}
