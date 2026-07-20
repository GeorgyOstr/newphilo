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
	pthread_mutex_lock(philo->write);
	if (!gettimeofday(&curr, NULL))
		return (pthread_mutex_unlock(philo->write),
			pthread_mutex_unlock(philo->finish), true);
	printf("%ld.%06ld %u", curr.tv_sec, curr.tv_usec, philo->philo_num);
	if (stat == SLEEPING)
		printf("is sleeping");
	else if (stat == EATING)
		printf("is eating");
	else if (stat == THINKING)
		printf("is thinking");
	else if (stat == TAKEN_FORK)
		printf("has taken a fork");
	pthread_mutex_unlock(philo->write);
	pthread_mutex_unlock(philo->finish);
	return (false);
}
