#include "./constant.h"
#include "./unp.h"

// 一次性读取MAXLINE个字符，存在static变量中，每次调用该函数返回一个字符
// 当字符全部返回完，即read_cnt=0的时候，在重新read一次，相对于旧版本的
// 代码，减少了I/O操作
static int my_read(int fd, char *ptr) {
    static int read_cnt = 0;
    static char *read_ptr;
    static char read_buf[MAXLINE];

    if (read_cnt <= 0) {
    again:
        if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR) {
                goto again;
            }
            return (-1);
        } else if (read_cnt == 0) {
            return (0);
        }
        read_ptr = read_buf;
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return (1);
}

int readline(int fd, void *vptr, int maxlen) {
    int n, rc;
    char c, *ptr;

    ptr = (char *)vptr;
    for (n = 1; n < maxlen; n++) {
        if ((rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n') {
                break;
            }
        } else if (rc == 0) {
            if (n == 1) {
                return (0);
            } else {
                break;
            }
        } else {
            return (-1);
        }
    }

    *ptr = 0;
    return (n);
}

int Readline(int fd, void *ptr, int maxlen) {
    int n;

    if ((n = readline(fd, ptr, maxlen)) < 0) {
        LogErrQuit("Readline error");
    }
    return (n);
}
