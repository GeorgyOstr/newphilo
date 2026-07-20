/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:40:10 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:40:11 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Not handling overflow
struct timeval	*time_add(struct timeval *t1, struct timeval *t2)
{
	t1->tv_sec = (unsigned)t1->tv_sec + (unsigned)t2->tv_sec
		+ ((unsigned)t1->tv_usec + (unsigned)t2->tv_usec) / 1000000;
	t1->tv_usec = ((unsigned)t1->tv_usec + (unsigned)t2->tv_usec) % 1000000;
	return (t1);
}

void	unsigned_to_time(struct timeval *t, unsigned int v)
{
	t->tv_sec = v / 1000;
	t->tv_sec = (v % 1000) * 1000;
}

void	time_copy(struct timeval *t1, struct timeval *t2)
{
	t1->tv_sec = t2->tv_sec;
	t1->tv_usec = t2->tv_usec;
}

bool	time_more_eq(struct timeval *m, struct timeval *l)
{
	if (m->tv_sec > l->tv_sec)
		return (true);
	else if (m->tv_sec < l->tv_sec)
		return (false);
	if (m->tv_usec > l->tv_usec)
		return (true);
	return (false);
}
