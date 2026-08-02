/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 15:30:30 by gostroum          #+#    #+#             */
/*   Updated: 2026/08/02 15:30:47 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_time(t_philo *philo, struct timeval *curr)
{
	if (gettimeofday(curr, NULL))
	{
		philo_set_error(philo, GETTIME_ERROR);
		return (true);
	}
	return (false);
}

bool	get_relative_time(t_philo *philo, struct timeval *curr)
{
	if (gettimeofday(curr, NULL) || !time_sub(curr, philo->sim_start))
	{
		philo_set_error(philo, GETTIME_ERROR);
		return (true);
	}
	return (false);
}
