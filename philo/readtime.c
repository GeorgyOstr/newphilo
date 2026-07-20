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

bool	readtime(char *s, struct timeval *arg)
{
	unsigned	val;

	if (readarg(s, &val))
		return (true);
	unsigned_to_time(arg, val);
	return (false);
}
