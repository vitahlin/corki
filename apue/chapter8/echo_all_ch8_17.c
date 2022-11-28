/**
 * 回显所有命令行参数和及全部环境表
 */

#include "../lib/apue.h"

int main(int argc, const char **argv) {
    extern char **environ;

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] %s\n", i, argv[i]);
    }

    char **ptr;
    for (ptr = environ; *ptr != 0; ptr++) {
        printf("%s\n", *ptr);
    }

    return 0;
}
