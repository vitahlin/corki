
#include "./unp.h"

void perrorAndQuit(const char *msg) {
    perror(msg);
    exit(1);
}


void printfAndQuit(const char *msg) {
    printf("%s\n", msg);
    exit(1);
}