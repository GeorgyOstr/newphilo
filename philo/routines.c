#include "philo.h"

void    philo_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    
    while (1)
    {
        pthread_mutex_lock(philo->finish);
        if (*philo->sim_finished)
            return (pthread_mutex_unlock(philo->finish), arg);
        pthread_mutex_unlock(philo->finish);
        if (think(philo))
            break;
        if (eat(philo))
            break;
        if (print_status(philo, SLEEPING))
            break;
        if (busy_sleep(philo, philo->args->time_to_sleep))
            break;
    }
    return (arg);
}

bool think(t_philo *philo)
{
    if (print_status(philo, THINKING))
		return (true);
    if (philo->philo_num % 2 == 0 && philo->eat_count == 0)
	{
		if (busy_sleep(philo, philo->args->time_to_eat / 2))
			return (true);
	}
    while (grabbing_fork(philo, 0))
		if (check_dead(philo))
			return (true);
	if (print_status(philo, TAKEN_FORK))
		return (release_fork(philo, 0), true);
	while (grabbing_fork(philo, 1))
		if (check_dead(philo))
			return (release_fork(philo, 0), true);
	if (print_status(philo, TAKEN_FORK))
		return (release_fork(philo, 0), release_fork(philo, 1), true);
	return (false);
}

bool eat(t_philo *philo)
{
    if (print_status(philo, EATING))
		return (true);
	if (philo->eat_count == philo->args->number_of_eat_to_finish)
	{
		pthread_mutex_lock(philo->finish);
		*philo->eat_enough_count += 1;
		if (*philo->eat_enough_count == philo->args->number_of_philos
			&& !*philo->sim_finished)
			*philo->sim_finished = 1;
		pthread_mutex_unlock(philo->finish);
	}
	if (busy_sleep(philo, philo->args->time_to_eat))
		return (release_fork(philo, 0), release_fork(philo, 1), 1);
	return (release_fork(philo, 0), release_fork(philo, 1), 0);
}

bool    grabbing_fork(t_philo *philo, int num)
{
	pthread_mutex_lock(philo->forks_locks[num]);
	if (*philo->forks_states[num] == true)
		return (pthread_mutex_unlock(philo->forks_locks[num]), true);
	*philo->forks_states[num] = true;
	pthread_mutex_unlock(philo->forks_locks[num]);
	return (false);
}

void    release_fork(t_philo *philo, unsigned num)
{
    pthread_mutex_lock(philo->forks_locks[num]);
    *philo->forks_states[num] = false;
    pthread_mutex_unlock(philo->forks_locks[num]);
}

int	busy_sleep(t_philo *philo, unsigned duration)
{
	struct timeval     start;

	if (gettimeofday(&start, NULL))
        return (false);
	while (get_time() - start < duration)
		if (check_dead(philo))
			return (1);
	return (0);
}