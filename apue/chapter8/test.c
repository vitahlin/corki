/**
 * fork函数，子进程对变量所做的改变并不影响父进程该变量的值
 */

#include "../lib/apue.h"

int main(int argc, const char **argv) {
    printf("test");
    return 0;
}
