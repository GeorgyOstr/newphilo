/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readarg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:38:18 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:38:19 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	readarg(char *s, unsigned int *arg)
{
	unsigned int i;

	i = 0;
	while (s[i])
	{
		if (!('0' <= s[i] && s[i] <= '9') || UINT_MAX / 10 < *arg
			|| UINT_MAX < *arg * 10 + (unsigned int)(s[i] - '0'))
			return (true);
		*arg *= 10;
		*arg += (unsigned int)(s[i] - '0');
		i++;
	}
	if (arg == 0)
		return (true);
	return (false);
}
