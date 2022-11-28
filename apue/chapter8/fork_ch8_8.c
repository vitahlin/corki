/**
 * fork两次以避免僵死进程
 * 如果一个进程fork一个子进程，但不要它等待子进程终止，也不希望子进程处于僵死状态直到父进程终止，实现这一要求的诀窍是调用fork两次
 * 第二个子进程调用sleep以保证在打印父进程ID时第一个子进程已经终止，在fork之后，父进程和子进程都可继续执行，并且无法预知哪一个
 * 会先执行，在fork之后，如果不使第二个子进程休眠，那么它可能比其父进程先执行，于是它打印的父进程ID将是创建它的父进程，而不是init进程
 */

#include "../lib/apue.h"

int main(int argc, const char **argv) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        ErrorQuit("fork error");
    } else if (pid == 0) {
        // first child
        if ((pid = fork()) < 0) {
            ErrorQuit("fork error");
        } else if (pid > 0) {
            // parent from second fork == first child
            exit(0);
        }

        sleep(2);
        printf("second child, parent pid=%ld", (long) getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid) {
        ErrorQuit("fork error");
    }

    exit(0);
    return 0;
}