#include "philo.h"

bool    readarg(char *s, unsigned int *arg)
{
    unsigned int  i;

    i = 0;
    while (s[i])
    {
        if (!('0' <= s[i] && s[i] <= '9') || UINT_MAX / 10 < *arg || UINT_MAX < *arg * 10 + (unsigned int)(s[i] - '0'))
            return (true);
        *arg *= 10; 
        *arg += (unsigned int)(s[i] - '0');
        i++;
    }
    if (arg == 0)
        return (true);
    return (false);
}

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
	char	*p;
	size_t	i;

	p = s;
	i = 0;
	while (i++ < n)
		*(p++) = '\0';
}