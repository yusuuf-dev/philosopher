/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:25:00 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/06 09:25:01 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;
	long			curr_time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (curr_time);
}

void	ft_usleep(long time)
{
	long	st_time;

	st_time = get_current_time();
	while (get_current_time() - st_time < time)
	{
		usleep(500);
	}
}

void	print(t_data *data, int ph, char *state)
{
	long	time;

	pthread_mutex_lock(&data->write_mx);
	pthread_mutex_lock(&data->nb_mx);
	if (data->is_end)
	{
		pthread_mutex_unlock(&data->nb_mx);
		pthread_mutex_unlock(&data->write_mx);
		return ;
	}
	pthread_mutex_unlock(&data->nb_mx);
	time = get_current_time() - data->st_time;
	printf("%ld %d %s\n", time, ph, state);
	pthread_mutex_unlock(&data->write_mx);
}
