/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:38:57 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:38:58 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_dead(t_philo *philo)
{
	struct timeval	curr;

	if (gettimeofday(&curr, NULL)|| !time_sub(&curr,philo->sim_start))
	{
		pthread_mutex_lock(philo->finish);
		*philo->error = GETTIME_ERROR;
		*philo->sim_finished = true;
		pthread_mutex_unlock(philo->finish);		
		return (true);
	}
	if (time_more_eq(&curr, &philo->death_time))
		return (print_status(philo, DIED), true);
	return (false);
}
