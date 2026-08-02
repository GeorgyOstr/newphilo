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

bool	time_add(struct timeval *t1, struct timeval *t2)
{
	if (UINT_MAX - (unsigned)t1->tv_sec < (unsigned)t2->tv_sec || (UINT_MAX
			- (unsigned)t1->tv_sec == (unsigned)t2->tv_sec
			&& ((unsigned)t1->tv_usec + (unsigned)t2->tv_usec) / 1000000 == 1))
	{
		t1->tv_sec = 0;
		t1->tv_usec = 0;
		return (true);
	}
	t1->tv_sec = (unsigned)t1->tv_sec + (unsigned)t2->tv_sec
		+ ((unsigned)t1->tv_usec + (unsigned)t2->tv_usec) / 1000000;
	t1->tv_usec = ((unsigned)t1->tv_usec + (unsigned)t2->tv_usec) % 1000000;
	return (false);
}

struct timeval	*time_sub(struct timeval *t1, struct timeval *t2)
{
	if ((t1->tv_sec < t2->tv_sec) || (t1->tv_sec == t2->tv_sec
			&& t1->tv_usec < t2->tv_usec))
		return (NULL);
	t1->tv_sec = (unsigned)t1->tv_sec - (unsigned)t2->tv_sec;
	if (t1->tv_usec >= t2->tv_usec)
		t1->tv_usec = (unsigned)t1->tv_usec - (unsigned)t2->tv_usec;
	else
	{
		t1->tv_usec = 1000000 + (unsigned)t1->tv_usec - (unsigned)t2->tv_usec;
		t1->tv_sec--;
	}
	return (t1);
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
	if (m->tv_usec >= l->tv_usec)
		return (true);
	return (false);
}

bool	time_more(struct timeval *m, struct timeval *l)
{
	if (m->tv_sec > l->tv_sec)
		return (true);
	else if (m->tv_sec < l->tv_sec)
		return (false);
	if (m->tv_usec > l->tv_usec)
		return (true);
	return (false);
}
