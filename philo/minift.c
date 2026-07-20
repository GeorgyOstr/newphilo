/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minift.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:39:13 by gostroum          #+#    #+#             */
/*   Updated: 2026/07/20 22:39:14 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	val;

	if (!nmemb || !size)
		return (malloc(0));
	val = nmemb * size;
	if (val / nmemb != size)
		return (NULL);
	p = malloc(val);
	if (!p)
		return (NULL);
	ft_bzero(p, val);
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	char *p;
	size_t i;

	p = s;
	i = 0;
	while (i++ < n)
		*(p++) = '\0';
}
