
#include "./unp.h"

// fd：套接字描述符
// vptr: 存储字符串的指针
// 存储字符串的空间大小
int writen(int fd, const void* vptr, int n) {
    int nleft;
    int nwritten;
    const char* ptr;

    ptr = (char*)vptr;
    nleft = n;
    while (nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) <= 0) {
            if (errno == EINTR) {
                nwritten = 0;
            } else {
                return (-1);
            }
        }

        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

// fd：套接字描述符
// ptr: 存储字符串的指针
// 存储字符串的空间大小
void Writen(int fd, void* ptr, int nbytes) {
    if (writen(fd, ptr, nbytes) != nbytes) {
        LogErrQuit("Writen error.");
    }
}