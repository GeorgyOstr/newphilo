/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 15:27:19 by gostroum          #+#    #+#             */
/*   Updated: 2026/08/02 15:27:20 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_error(t_sim *sim, enum e_errors error)
{
	pthread_mutex_lock(sim->finish);
	sim->sim_finished = true;
	sim->error = error;
	pthread_mutex_unlock(sim->finish);
}

void	philo_set_error(t_philo *philo, enum e_errors error)
{
	pthread_mutex_lock(philo->finish);
	*philo->sim_finished = true;
	*philo->error = error;
	pthread_mutex_unlock(philo->finish);
}
