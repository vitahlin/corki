/**
 * 书上介绍内容：
 * 运行该程序时，结果具有随机性。通常在信号处理程序经过多次迭代返回时，该程序将由SIGSEGV信号终止。
 * 检查core文件，从中可以看到main函数已经调用getpwnam，但当getpwnam调用free时，信号处理程序中断了它的运行，并调用getpwnam,进而再次调用free。
 * 在信号处理程序调用free而主程序也在调用freee时，malloc和free维护的数据结构就出现了损坏。
 * 偶然，程序仍会运行若干秒，然后因产生SIGSEGV信号而终止。
 * 在捕捉到信号后，若main函数仍正确运行，其返回值有时正确，有时错误。
 * 从此实例可以看出，如果在信号处理程序中调用一个非可重入函数，则其结果是不可预知的。
 *
 * 实际运行结果：
 * Getpwnam error: Undefined error: 0
 *
 * Todo：验证实际运行结果与书上说明的一致性
 */

#include <pwd.h>
#include <sys/types.h>

#include "./../lib/apue.h"

static void MyAlarm(int sig_num) {
    struct passwd* root_ptr;

    printf("\nIn signal handler\n");

    // getpwnam获取用户登录相关信息
    if ((root_ptr = getpwnam("root")) == NULL) {
        ErrorSystem("getpwnam(root) error");
    }

    // 在1秒后向调用alarm的进程发送一个SIGALRM信号
    alarm(1);
}

int main(int argc, const char** argv) {
    struct passwd* ptr;

    signal(SIGALRM, MyAlarm);

    alarm(1);

    for (;;) {
        if ((ptr = getpwnam("sar")) == NULL) {
            ErrorSystem("Getpwnam error");
        }

        if (strcmp(ptr->pw_name, "sar") != 0) {
            printf("return value corrupted, pw_name=%s\n", ptr->pw_name);
        }
    }

    return 0;
}