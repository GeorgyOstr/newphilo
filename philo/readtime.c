#include "philo.h"

bool	readtime(char *s, struct timeval *arg)
{
	unsigned	val;

	if (readarg(s, &val))
		return (true);
	unsigned_to_time(arg, val);
	return (false);
}
