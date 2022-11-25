/**
 * vfork函数，与文件01_08_01fork.cpp对比
 *  1.
 * 不需要再让父进程sleep，因为子进程调用exit或exec之前，内核会使父进程处于休眠状态
 *  2.
 * 子进程对变量做增1的操作，结果改变了父进程中的变量值，因为子进程在父进程的地址空间中运行
 */

#include "../lib/apue.h"

int global_var = 6;

int main(int argc, const char **argv) {
    int var = 88;
    pid_t pid;

    printf("Before fork, var=%d\n", var);

    if ((pid = vfork()) < 0) {
        ErrorQuit("fork error");
    } else if (pid == 0) {
        global_var++;
        var++;

        // 子进程需要调用exit父进程才能运行
        _exit(0);
    }

    printf("pid=%d, global var=%d, var=%d\n", getpid(), global_var, var);

    return 0;
}
