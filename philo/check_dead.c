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

	if (gettimeofday(&curr, NULL))
	{
		*philo->error = GETTIME_ERROR;
		return (true);
	}
	if (time_more_eq(&curr, &philo->death_time))
		return (true);
	return (false);
}
