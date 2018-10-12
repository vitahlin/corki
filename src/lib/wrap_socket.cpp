#include "./unp.h"

int Socket(int domain, int type, int protocol)
{
	int n;
	if ((n = socket(domain, type, protocol)) < 0)
	{
		LogErrQuit("socker error");
	}

	return n;
}
