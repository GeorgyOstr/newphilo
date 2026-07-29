/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:39:46 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:39:59 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	think(t_philo *philo);
static bool	eat(t_philo *philo);
static bool	grabbing_fork(t_philo *philo, int num);
static void	release_fork(t_philo *philo, unsigned int num);

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	struct timeval	curr;

	philo = (t_philo *)arg;
	while(!*philo->sim_finished)
	{
		if (gettimeofday(&curr, NULL))
			return (*philo->error = GETTIME_ERROR, arg);
		if (time_more_eq(&curr, philo->sim_start))
			break;
	}
	while (!*philo->sim_finished)
	{
		if (think(philo))
			break ;
		if (eat(philo))
			break ;
		if (print_status(philo, SLEEPING))
			break ;
		if (busy_sleep(philo, &philo->args->time_to_sleep))
			break ;
	}
	return (arg);
}

static bool	think(t_philo *philo)
{
	if (print_status(philo, THINKING))
		return (true);
	if (philo->philo_num % 2 == 0 && philo->eat_count == 0)
	{
		if (busy_sleep(philo, &philo->args->time_to_eat))
			return (true);
	}
	while (grabbing_fork(philo, 0)&&!*philo->sim_finished)
		usleep(USLEEP_TIME);
	if (print_status(philo, TAKEN_FORK))
		return (release_fork(philo, 0), true);
	while (grabbing_fork(philo, 1)&&!*philo->sim_finished)
		usleep(USLEEP_TIME);
	if (print_status(philo, TAKEN_FORK))
		return (release_fork(philo, 0), release_fork(philo, 1), true);
	return (false);
}

static bool	eat(t_philo *philo)
{
	if (print_status(philo, EATING))
		return (release_fork(philo, 0), release_fork(philo, 1), true);
	if (busy_sleep(philo, &philo->args->time_to_eat))
		return (release_fork(philo, 0), release_fork(philo, 1), true);
	return (release_fork(philo, 0), release_fork(philo, 1), false);
}

static bool	grabbing_fork(t_philo *philo, int num)
{
	pthread_mutex_lock(philo->forks_locks[num]);
	if (*philo->forks_states[num] == true)
		return (pthread_mutex_unlock(philo->forks_locks[num]), true);
	*philo->forks_states[num] = true;
	pthread_mutex_unlock(philo->forks_locks[num]);
	return (false);
}

static void	release_fork(t_philo *philo, unsigned int num)
{
	pthread_mutex_lock(philo->forks_locks[num]);
	*philo->forks_states[num] = false;
	pthread_mutex_unlock(philo->forks_locks[num]);
}
