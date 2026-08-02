/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 18:09:26 by gostroum          #+#    #+#             */
/*   Updated: 2026/08/02 18:10:32 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	halftime(struct timeval *t, struct timeval *original);
static bool	think_odd(t_philo *philo);

bool	think_odd_even(t_philo *philo)
{
	struct timeval	h;

	halftime(&h, &philo->args->time_to_eat);
	if (philo->philo_num % 2 == 0 && philo->eat_count == 0)
	{
		if (sleep_time(philo, &h))
			return (true);
	}
	if (philo->args->number_of_philos % 2 == 1)
		if (think_odd(philo))
			return (true);
	return (false);
}

static void	halftime(struct timeval *t, struct timeval *original)
{
	t->tv_sec = original->tv_sec / 2;
	t->tv_usec = original->tv_usec / 2;
	if (original->tv_sec % 2 == 1)
		t->tv_usec += (unsigned)500000;
}

static bool	think_odd(t_philo *philo)
{
	struct timeval	h;
	struct timeval	half_sleep;
	struct timeval	val;

	halftime(&h, &philo->args->time_to_eat);
	halftime(&half_sleep, &philo->args->time_to_sleep);
	time_copy(&val, &philo->args->time_to_eat);
	if (philo->philo_num == philo->args->number_of_philos
		&& philo->eat_count == 0)
	{
		if (sleep_time(philo, &h) || sleep_time(philo,
				&philo->args->time_to_eat))
			return (true);
	}
	if (philo->eat_count > 0 && time_more(&val, &half_sleep))
	{
		time_sub(&val, &half_sleep);
		if (sleep_time(philo, &val))
			return (true);
	}
	return (false);
}
