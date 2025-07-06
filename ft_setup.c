/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:25:40 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/06 09:25:41 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex_forks(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->nb_mx, NULL) != 0)
		return (ft_clean(data, 1));
	i = 0;
	while (i < data->nb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&data->forks[i]);
			}
			pthread_mutex_destroy(&data->nb_mx);
			return (ft_clean(data, 1));
		}
		i++;
	}
	return (0);
}

static int	init_mutex_l_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		if (pthread_mutex_init(&data->last_meals_mx[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&data->last_meals_mx[i]);
			}
			i = 0;
			while (i < data->nb)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i++;
			}
			pthread_mutex_destroy(&data->nb_mx);
			return (ft_clean(data, 1));
		}
		i++;
	}
	return (0);
}

int	ft_setup(t_data *data, int ac, char **av)
{
	data->nb = custom_atoi(av[1]);
	data->init_nb = 0;
	data->tm_die = custom_atoi(av[2]);
	data->tm_eat = custom_atoi(av[3]);
	data->tm_sleep = custom_atoi(av[4]);
	memset(data->last_meals, 0, data->nb * sizeof(int));
	if (ac == 6)
	{
		data->philo_meals = custom_atoi(av[5]);
		memset(data->total_meals, 0, data->nb * sizeof(int));
	}
	else
	{
		data->total_meals = NULL;
		data->philo_meals = 0;
	}
	data->st_time = get_current_time();
	if (data->st_time == -1)
		return (ft_clean(data, 4));
	data->is_end = 0;
	if (pthread_mutex_init(&data->write_mx, NULL) != 0)
		return (ft_clean(data, 1));
	if (init_mutex_forks(data) || init_mutex_l_meals(data))
		return (1);
	return (0);
}
