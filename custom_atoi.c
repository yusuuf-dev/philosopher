#include "philo.h"

long	custom_atoi(char *str)
{
	size_t	i;
	long	r;

	i = 0;
	r = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r > 2147483647)
			return (-1);
		i++;
	}
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i])
		return (0);
	return (r);
}
