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

	if (gettimeofday(&end, NULL) || !time_sub(&end, philo->sim_start))
		return (*philo->error = GETTIME_ERROR, true);
	time_add(&end, duration);
	while (1)
	{
		if (gettimeofday(&curr, NULL) || !time_sub(&curr, philo->sim_start))
			return (*philo->error = GETTIME_ERROR, true);
		if (time_more_eq(&curr, &philo->death_time))
			return (print_status(philo, DIED), true);
		if (time_more_eq(&curr, &end))
			return (false);
		usleep(USLEEP_TIME);
	}
	return (false);
}
