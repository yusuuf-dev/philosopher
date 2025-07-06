/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:25:56 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/06 10:53:56 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_destroy(&data->last_meals_mx[i]);
		i++;
	}
	pthread_mutex_destroy(&data->nb_mx);
	return (ft_free(data, status));
}
