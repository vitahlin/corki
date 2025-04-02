#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int anetTcpServer(char *server_net_error, int port, char *bindaddr, int backlog);


