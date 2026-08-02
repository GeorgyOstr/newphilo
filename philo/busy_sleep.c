/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   busy_sleep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:36:59 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:37:00 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	busy_sleep(t_philo *philo, struct timeval *duration)
{
	struct timeval	end;
	struct timeval	curr;

	if (get_relative_time(philo, &end))
		return (true);
	time_add(&end, duration);
	while (1)
	{
		if (get_relative_time(philo, &curr))
			return (true);
		if (time_more_eq(&curr, &philo->death_time))
			return (print_status(philo, DIED), true);
		if (time_more_eq(&curr, &end))
			return (false);
		pthread_mutex_lock(philo->finish);
		if (*philo->sim_finished)
			return (pthread_mutex_unlock(philo->finish), true);
		pthread_mutex_unlock(philo->finish);
		usleep(USLEEP_TIME);
	}
	return (false);
}
