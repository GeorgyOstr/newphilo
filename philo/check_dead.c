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

	pthread_mutex_lock(philo->finish);
	if (*philo->sim_finished)
		return (pthread_mutex_unlock(philo->finish), true);
	pthread_mutex_unlock(philo->finish);
	if (get_relative_time(philo, &curr))
		return (true);
	if (time_more_eq(&curr, &philo->death_time))
		return (print_status(philo, DIED), true);
	return (false);
}
