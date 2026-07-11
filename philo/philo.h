/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 11:52:21 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/11 12:12:05 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_errors
{
	ARGUMENTS_ERROR,
	ATOI_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR,
	GETTIME_ERROR
};

enum				e_status
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FINISHED
};

typedef struct s_args
{
	size_t			number_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			number_of_eat_to_finish;
}					t_args;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	*forks_locks[2];
	pthread_mutex_t	*write;
	pthread_mutex_t	*finish;
	t_args			*args;
	bool			*forks_states[2];
	bool			*sim_finished;
	size_t			*eat_enough_count;
	size_t			philo_num;
	size_t			eat_count;
	timeval			last_ate_time;
	timeval 		*sim_start;
}					t_philo;

typedef struct s_sim
{
	t_philo			*philos;
	pthread_mutex_t	*forks_locks;
	pthread_mutex_t	*write;
	pthread_mutex_t	*finish;
	bool			*forks_states;
	bool			sim_finished;
	timeval			sim_start;
	size_t			eat_enough_count;
}					t_sim;

#endif