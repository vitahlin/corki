
#include "./unp.h"

void Write(int fd, const void *buff, int count)
{
	int n;
	if ((n = write(fd, buff, count)) != count)
	{
		LogErrQuit("Write error");
	}
}
