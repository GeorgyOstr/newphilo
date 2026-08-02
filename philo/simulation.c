/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:38:34 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:38:36 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	threads(t_sim *sim);

void	start(t_sim *sim)
{
	if (gettimeofday(&sim->sim_start, NULL))
	{
		sim->error = GETTIME_ERROR;
		return ;
	}
	time_add(&sim->sim_start, &(struct timeval){0, SIM_DELAY});
	threads(sim);
}

static void	threads(t_sim *sim)
{
	unsigned int	i;
	unsigned int	cnt;

	i = 0;
	while (i < sim->args.number_of_philos)
	{
		if (pthread_create(&sim->philos[i].thread_id, NULL, &philo_routine,
				&sim->philos[i]))
		{
			set_error(sim, THREAD_ERROR);
			break ;
		}
		i++;
	}
	cnt = i;
	i = 0;
	while (i < cnt)
	{
		if (pthread_join(sim->philos[i++].thread_id, NULL))
		{
			set_error(sim, THREAD_ERROR);
			break ;
		}
	}
}
