/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:37:22 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:37:23 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_sim *sim)
{
	unsigned i;

	i = 0;
	while (i < sim->args.number_of_philos)
		pthread_mutex_destroy(&sim->forks_locks[i++]);
	pthread_mutex_destroy(sim->finish);
	pthread_mutex_destroy(sim->write);
	free(sim->forks_states);
	free(sim->forks_locks);
	free(sim->philos);
}
