/**
 * 调用自己实现的system函数示例
 */

#include "../lib/apue.h"

int main(int argc, const char **argv) {
    int status;

    if ((status = MySystem("date")) < 0) {
        ErrorSystem("MySystem error");
    }
    PrintExit(status);

    if ((status = MySystem("nosuchcommand")) < 0) {
        ErrorSystem("MySystem error");
    }
    PrintExit(status);

    if ((status = MySystem("who; exist 44")) < 0) {
        ErrorSystem("MySystem error");
    }
    PrintExit(status);

    return 0;
}
