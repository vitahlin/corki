
#include "./unp.h"

char *Fgets(char *ptr, int n, FILE *stream) {
    char *rptr;

    // 从文件结构体指针stream中读取数据，每次读取一行，数据保存在ptr指针中，每次最多读取n-1个字符
    // 成功返回第一个指针ptr
    if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream)) {
        LogErr("Fgets error.");
    }

    return rptr;
}

void Fputs(const char *ptr, FILE *stream) {
    if (fputs(ptr, stream) == EOF) {
        LogErr("Fputs error.");
    }
}