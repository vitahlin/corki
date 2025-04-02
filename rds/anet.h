#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int anetTcpServer(char *server_net_error, int port, char *bindaddr, int backlog);

int anetSetBlock(char *err, int fd, int non_block);


