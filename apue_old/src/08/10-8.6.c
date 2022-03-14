/**
 * 习题8.6
 * 编写一个程序创建一个僵死进程，然后调用system执行ps(l)命令以验证该进程是僵死进程
 */

#include "./../lib/apue.h"

int main(int argc, const char** argv) {
    pid_t pid;

    int status;

    printf("习题8.6\n");
    printf(
        "编写一个程序创建一个僵死进程，然后调用system函数执行ps命令以严重该进程"
        "是僵死进程\n");

    if ((pid = fork()) < 0) {
        ErrorQuit("Fork error");
    } else if (pid == 0) {
        exit(0);
    }

    printf("Child process pid %d\n", pid);
    if ((status = MySystem("ps -el")) < 0) {
        ErrorSystem("MySystem error");
    }

    return 0;
}
