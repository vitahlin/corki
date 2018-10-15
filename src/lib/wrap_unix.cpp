
#include "./unp.h"

void Write(int fd, const void *buff, int count)
{
	int n;
	if ((n = write(fd, buff, count)) != count)
	{
		LogErrQuit("Write error");
	}
}

void Close(int fd)
{
	if (close(fd) == -1)
	{
		LogErrQuit("Close error.");
	}
}
