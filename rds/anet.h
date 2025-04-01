#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "string.h"

static int anetTcpServer(char *err, int port, char *bindaddr, int backlog);
