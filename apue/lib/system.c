#include "apue.h"

int MySystem(const char *cmd_string) {
    pid_t pid;
    int status;

    if (cmd_string == NULL) {
        return 1;
    }

    if ((pid = fork()) < 0) {
        status = -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd_string, (char *) 0);

        /**
         *  如果无法启动shell命令，system将返回127
         * 调用_exit而不是exit，为了防止任一标准I/O缓冲在子进程中被冲洗
         * 子进程正常执行则不会执行此语句
         */
        _exit(127);
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;
                break;
            }
        }
    }

    return status;
}

/**
 * 打印进程终止状态
 */
void PrintExit(int status) {
    if (WIFEXITED(status)) {
        printf("normal termination, exit status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("abnormal termination, signal number=%d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
               WCOREDUMP(status) ? "(core file generated)" : "");
#else
        "");
#endif
    } else if (WIFSTOPPED(status)) {
        printf("child stopped, signal number=%d\n", WSTOPSIG(status));
    }
}