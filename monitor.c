/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:25:33 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/06 09:50:16 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat_all_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_lock(&data->last_meals_mx[i]);
		if (data->total_meals[i] < data->philo_meals)
		{
			pthread_mutex_unlock(&data->last_meals_mx[i]);
			return (0);
		}
		pthread_mutex_unlock(&data->last_meals_mx[i]);
		i++;
	}
	pthread_mutex_lock(&data->nb_mx);
	data->is_end = 1;
	pthread_mutex_unlock(&data->nb_mx);
	return (1);
}

static void	*stop_simulation(t_data *data, int ph)
{
	long	curr_time;

	pthread_mutex_unlock(&data->last_meals_mx[ph]);
	pthread_mutex_lock(&data->nb_mx);
	data->is_end = 1;
	pthread_mutex_unlock(&data->nb_mx);
	curr_time = get_current_time() - data->st_time;
	pthread_mutex_lock(&data->write_mx);
	printf("%ld %d died\n", curr_time, ph);
	pthread_mutex_unlock(&data->write_mx);
	if (data->nb == 1)
	{
		pthread_mutex_unlock(&data->forks[ph]);
	}
	return (NULL);
}

static void	wait_init_threads(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->nb_mx);
		if (data->init_nb >= data->nb)
		{
			pthread_mutex_unlock(&data->nb_mx);
			break ;
		}
		pthread_mutex_unlock(&data->nb_mx);
		usleep(50);
	}
}

void	*monitor(void *arg)
{
	t_data	*data;
	long	curr_time;
	int		i;

	data = (t_data *)arg;
	wait_init_threads(data);
	while (1)
	{
		ft_usleep(1);
		i = 0;
		while (i < data->nb)
		{
			pthread_mutex_lock(&data->last_meals_mx[i]);
			curr_time = get_current_time() - data->st_time;
			if (curr_time - data->last_meals[i] > (long)data->tm_die)
				return (stop_simulation(data, i));
			pthread_mutex_unlock(&data->last_meals_mx[i]);
			i++;
		}
		if (data->philo_meals != 0 && eat_all_meals(data))
			break ;
	}
	return (NULL);
}
