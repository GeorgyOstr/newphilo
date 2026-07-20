#include "philo.h"

struct timeval time_add(struct timeval *t1, struct timeval *t2)
{
    return (*t1);
}

void    unsigned_to_time(struct timeval *t, unsigned int)
{

}

void    time_copy(struct timeval *t1, struct timeval *t2)
{

}
struct timeval time_inc(struct timeval *t1, struct timeval *t2)
{

}

bool time_more_eq(struct timeval *m, struct timeval *l)
{
    if (m->tv_sec > l->tv_sec)
        return (true);
    else if (m->tv_sec < l->tv_sec)
        return (false);
    if (m->tv_usec > l->tv_usec)
        return (true);
    return (false);
}