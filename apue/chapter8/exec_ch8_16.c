/**
 * exec函数示例
 */

#include "../lib/apue.h"

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(int argc, const char **argv) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        ErrorQuit("Fork error");
    } else if (pid == 0) {
        /**
         * execle要求一个路径名和一个特定的环境
         */
        if (execle("./08-8_17-echoall", "echoall", "myarg1", "MY ARG2",
                   (char *) 0, env_init) < 0) {
            ErrorQuit("Execle error");
        }
    }

    if (waitpid(pid, NULL, 0) < 0) {
        ErrorQuit("wait error");
    }

    if ((pid = fork()) < 0) {
        ErrorQuit("Fork error");
    } else if (pid == 0) {
        /**
         * 用一个文件名，并将调用者的环境传送给新程序
         * execlp在这里能够工作是因为目录/home/sar/bin是当前路径前缀之一
         */
        if (execlp("08-8_17-echoall", "echoall", "only 1 arg", (char *) 0,
                   env_init) < 0) {
            ErrorQuit("Execlp error");
        }
    }

    return 0;
}
