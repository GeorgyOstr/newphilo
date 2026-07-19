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
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define USLEEP_TIME	10

enum				e_errors
{
	NO_ERROR,
	ARGUMENTS_ERROR,
	ATOI_ERROR,
	MALLOC_ERROR,
	MUTEX_INIT_ERROR,
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
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_eat_to_finish;
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
	unsigned int	*eat_enough_count;
	unsigned int	philo_num;
	unsigned int	eat_count;
	struct timeval	last_ate_time;
	struct timeval	*sim_start;
	enum e_errors	*error;
}					t_philo;

typedef struct s_sim
{
	t_philo			*philos;
	pthread_mutex_t	*forks_locks;
	pthread_mutex_t	*write;
	pthread_mutex_t	*finish;
	bool			*forks_states;
	bool			sim_finished;
	struct timeval	sim_start;
	unsigned int	eat_enough_count;
	t_args			args;
	enum e_errors	error;
}					t_sim;

bool				readarg(char *s, unsigned int *arg);

void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
struct	timeval add_timeval(struct timeval *t1, struct timeval *t2);
void 	start(t_sim *sim);
void 	clean(t_sim *sim);
void    *philo_routine(void *arg);
bool 	print_status(t_philo *philo, enum e_status stat);




#endif