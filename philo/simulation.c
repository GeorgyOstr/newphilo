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
static void	set_start_time(t_sim *sim);

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
	while (i < sim->args.number_of_philos)
	{
		if (pthread_create(&sim->philos[i].thread_id, NULL, &philo_routine,
				&sim->philos[i]))
		{
			pthread_mutex_lock(sim->finish);
			sim->sim_finished = true;
			sim->error = THREAD_ERROR;
			pthread_mutex_unlock(sim->finish);
			i++;
			break ;
		}
	}
	i--;
	set_start_time(sim);
	while (i > 0)
		pthread_join(sim->philos[i--].thread_id, NULL);
}

static void	set_start_time(t_sim *sim)
{
	unsigned int	i;

	time_add(&sim->sim_start, &(struct timeval){0, SIM_DELAY});
	i = 0;
	while (i < sim->args.number_of_philos)
	{
		time_copy(&sim->philos[i].death_time, &sim->sim_start);
		time_add(&sim->philos[i].death_time, &sim->args.time_to_die);
		i++;
	}
}
