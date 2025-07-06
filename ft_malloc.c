/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:25:50 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/06 09:47:18 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	failed_malloc(t_data *data, int status)
{
	if (status > 5)
		free(data->last_meals);
	if (status > 4)
		free(data->last_meals_mx);
	if (status > 3)
		free(data->phs);
	if (status > 2)
		free(data->forks);
	if (status > 1)
		free(data);
	ft_putstr_fd("failed malloc\n", 2);
	return (1);
}

static int	init_nbs(t_data **data, int ac, int nb)
{
	(*data)->last_meals = malloc(nb * sizeof(long));
	if (!(*data)->last_meals)
		return (failed_malloc(*data, 5));
	memset((*data)->last_meals, 0, nb * sizeof(long));
	if (ac == 6)
	{
		(*data)->total_meals = malloc(nb * sizeof(int));
		if (!(*data)->total_meals)
			return (failed_malloc(*data, 6));
		memset((*data)->total_meals, 0, nb * sizeof(int));
	}
	return (0);
}

int	ft_malloc(t_data **data, int ac, int nb)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (1);
	memset(*data, 0, sizeof(t_data));
	(*data)->forks = malloc(nb * sizeof(pthread_mutex_t));
	if (!(*data)->forks)
		return (failed_malloc(*data, 2));
	memset((*data)->forks, 0, nb * sizeof(pthread_mutex_t));
	(*data)->phs = malloc(nb * sizeof(pthread_t));
	if (!(*data)->phs)
		return (failed_malloc(*data, 3));
	memset((*data)->phs, 0, nb * sizeof(pthread_t));
	(*data)->last_meals_mx = malloc(nb * sizeof(pthread_mutex_t));
	if (!(*data)->last_meals_mx)
		return (failed_malloc(*data, 4));
	memset((*data)->last_meals_mx, 0, nb * sizeof(pthread_mutex_t));
	if (init_nbs(data, ac, nb))
		return (1);
	return (0);
}
