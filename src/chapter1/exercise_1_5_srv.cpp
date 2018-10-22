/*============================================================================
* Created       : 2018-10-15 17:25
* Last modified : 2018-10-15 17:25
* Filename      : exercise_1_5_srv.cpp
* Description   :
*   习题1.5
*
=============================================================================*/

#include <time.h>
#include "../lib/unp.h"
#include "./../lib/constant.h"

int main(int argc, char* argv[]) {
    int listen_fd, conn_fd;
    struct sockaddr_in serv_addr;

    char buff[MAXLINE];
    time_t ticks;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serv_addr.sin_port = htons(9876);

    Bind(listen_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    Listen(listen_fd, LISTENQ);

    cout << "Server is running..." << endl;
    for (;;) {
        conn_fd = Accept(listen_fd, (struct sockaddr*)NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        for (int i = 0; i < strlen(buff); i++) {
            Write(conn_fd, buff + i, 1);
        }

        Close(conn_fd);
    }

    return 0;
}
