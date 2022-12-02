/**
 * 竞争条件示例
 *
 * 一个由子进程输出，一个由父进程输出。因为输出依赖于内核使这两个进程运行的顺序及每个进程运行的时间长度
 * 所以该程序包含一个竞争条件。
 * 程序中将标准输出设置为不带缓冲的，于是每个字符输出都需要调用一次write。本例的目的是使内核尽可能
 * 地多次在两个进程之间进行切换，以便演示竞争条件。
 *
 * 多次演示时，可能会出现父进程子进程交替输出对情况，这就是产生了竞争条件
 */

#include "../lib/apue.h"

static void output(char *str) {
    // 取消输出缓存
    setbuf(stdout, NULL);

    char *ptr;
    int c;
    for (ptr = str; (c = *ptr++) != 0;) {
        putc(c, stdout);
    }
}

int main(int argc, const char **argv) {
    pid_t pid;

    char child_str[] = "output from child\n";
    char parent_str[] = "output from parent\n";

    if ((pid = fork()) < 0) {
        ErrorQuit("fork error");
    } else if (pid == 0) {
        output(child_str);
    } else {
        output(parent_str);
    }

    return 0;
}
