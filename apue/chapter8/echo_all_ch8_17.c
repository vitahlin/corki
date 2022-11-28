/**
 * 回显所有命令行参数和及全部环境表
 */

#include "../lib/apue.h"

int main(int argc, const char **argv) {
    int i;
    char **ptr;
    extern char **environ;

    for (i = 0; i < argc; i++) {
        printf("argv[%d] %s\n", i, argv[i]);
    }

    for (ptr = environ; *ptr != 0; ptr++) {
        printf("%s\n", *ptr);
    }

    return 0;
}
