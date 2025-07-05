#include "philo.h"

int	ft_free(t_data *data, int status)
{
	free(data->total_meals);
	free(data->last_meals_mx);
	free(data->last_meals);
	free(data->phs);
	free(data->forks);
	free(data);
	if (status == 1)
		ft_putstr_fd("failed init mutex\n", 2);
	if (status == 2)
		ft_putstr_fd("failed create thread\n", 2);
	if (status == 3)
		ft_putstr_fd("failed join thread\n", 2);
	if (status == 4)
		ft_putstr_fd("gettimeofday failed\n", 2);
	return (1);
}

int	ft_clean(t_data *data, int status)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			ft_putstr_fd("failed destroy fork\n", 1);
		i++;
	}
	i = 0;
	while (i < data->nb)
	{
		if (pthread_mutex_destroy(&data->last_meals_mx[i]) != 0)
			ft_putstr_fd("failed destroy last meal\n", 1);
		i++;
	}
	if (pthread_mutex_destroy(&data->nb_mx) != 0)
		ft_putstr_fd("failed destroy nb_mx\n", 1);
	return (ft_free(data, status));
}
