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

	if (gettimeofday(&end, NULL))
		return (*philo->error = GETTIME_ERROR, true);
	time_add(&end, duration);
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
