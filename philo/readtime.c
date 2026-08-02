/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readtime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:38:10 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:38:11 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unsigned_to_time(struct timeval *t, unsigned int v);

bool	readtime(char *s, struct timeval *arg)
{
	unsigned int	val;

	if (readarg(s, &val))
		return (true);
	unsigned_to_time(arg, val);
	return (false);
}

static void	unsigned_to_time(struct timeval *t, unsigned int v)
{
	t->tv_sec = v / 1000;
	t->tv_usec = (v % 1000) * 1000;
}
