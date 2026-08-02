/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:37:51 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:37:52 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_status(t_philo *philo, enum e_status stat)
{
	struct timeval	curr;

	pthread_mutex_lock(philo->finish);
	if (*philo->sim_finished)
		return (pthread_mutex_unlock(philo->finish), false);
	pthread_mutex_lock(philo->write);
	if (gettimeofday(&curr, NULL) || !time_sub(&curr, philo->sim_start))
		return (pthread_mutex_unlock(philo->write), *philo->sim_finished = true, *philo->error = GETTIME_ERROR, pthread_mutex_unlock(philo->finish),
			 true);
	if (time_more_eq(&curr, &philo->death_time))
	{	
		*philo->sim_finished = true;
		printf("%ld%03ld %u died\n", curr.tv_sec, curr.tv_usec/1000, philo->philo_num);
		return (pthread_mutex_unlock(philo->write), pthread_mutex_unlock(philo->finish), false);
	}
	printf("%ld%03ld %u ", curr.tv_sec, curr.tv_usec/1000, philo->philo_num);
	if (stat == SLEEPING)
		printf("is sleeping");
	else if (stat == EATING)
	{
		philo->eat_count += 1;
		time_copy(&philo->death_time, &curr);
		time_add(&philo->death_time, &philo->args->time_to_die);
		if (philo->eat_count == philo->args->number_of_eat_to_finish)
		{
			*philo->eat_enough_count += 1;
			if (*philo->eat_enough_count == philo->args->number_of_philos)
				*philo->sim_finished = true;
		}
		printf("is eating");
	}
	else if (stat == THINKING)
		printf("is thinking");
	else if (stat == TAKEN_FORK)
		printf("has taken a fork");

	printf("\n");
	pthread_mutex_unlock(philo->write);
	pthread_mutex_unlock(philo->finish);
	return (false);
}
