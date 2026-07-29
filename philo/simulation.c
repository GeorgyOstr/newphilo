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
	threads(sim);
}

static void	threads(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	time_add(&sim->sim_start, &(struct timeval){0, SIM_DELAY});
	while (i < sim->args.number_of_philos)
	{
		if (pthread_create(&sim->philos[i].thread_id, NULL, &philo_routine,
				&sim->philos[i]))
		{
			pthread_mutex_lock(sim->finish);
			sim->sim_finished = true;
			sim->error = THREAD_ERROR;
			pthread_mutex_unlock(sim->finish);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < sim->args.number_of_philos)
	{
		if (pthread_join(sim->philos[i++].thread_id, NULL))
		{
			pthread_mutex_lock(sim->finish);
			sim->sim_finished = true;
			sim->error = THREAD_ERROR;
			pthread_mutex_unlock(sim->finish);
			break ;
		}
	}
}