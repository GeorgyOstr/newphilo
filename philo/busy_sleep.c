#include "philo.h"

bool	busy_sleep(t_philo *philo, struct timeval *duration)
{
	struct timeval	end;
	struct timeval	curr;

	if (gettimeofday(&end, NULL))
        return (*philo->error = GETTIME_ERROR, true);
	time_inc(&end, duration);
	while (true)
	{
		if (gettimeofday(&curr, NULL))
        	return (*philo->error = GETTIME_ERROR, true);
		if (time_more_eq(&curr, &philo->death_time))
			return (true);
		if (time_more_eq(&curr, &end))
			return (false);
	}
	return (false);
}