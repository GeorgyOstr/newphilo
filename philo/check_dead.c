#include "philo.h"

bool    check_dead(t_philo *philo)
{
    struct timeval  curr;

    if (gettimeofday(&curr, NULL))
    {
        *philo->error = GETTIME_ERROR;
        return (true);
    }
    if (time_more_eq(&curr, &philo->death_time))
        return (true);

    return (false);
}