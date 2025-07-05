#include "philo.h"

static int	is_simulation_end(t_data *data, int right_f, int ph)
{
	pthread_mutex_lock(&data->nb_mx);
	if (data->is_end)
	{
		pthread_mutex_unlock(&data->nb_mx);
		pthread_mutex_unlock(&data->forks[right_f]);
		pthread_mutex_unlock(&data->forks[ph]);
		return (1);
	}
	pthread_mutex_unlock(&data->nb_mx);
	return (0);
}

static void	last_philo_routine(t_data *data, int ph)
{
	int	right_f;

	right_f = (ph + 1) % data->nb;
	pthread_mutex_lock(&data->forks[right_f]);
	print(data, ph, "has taken a fork");
	pthread_mutex_lock(&data->forks[ph]);
	print(data, ph, "has taken a fork");
	pthread_mutex_lock(&data->last_meals_mx[ph]);
	data->last_meals[ph] = get_current_time() - data->st_time;
	print(data, ph, "is eating");
	if (data->philo_meals != 0)
		data->total_meals[ph]++;
	pthread_mutex_unlock(&data->last_meals_mx[ph]);
	if (is_simulation_end(data, right_f, ph))
		return ;
	ft_usleep(data->tm_eat);
	print(data, ph, "is sleeping");
	pthread_mutex_unlock(&data->forks[ph]);		
	pthread_mutex_unlock(&data->forks[right_f]);
	ft_usleep(data->tm_sleep);
	print(data, ph, "is thinking");
	if (data->nb % 2 && data->tm_sleep >= data->tm_eat)
		ft_usleep(data->tm_sleep);
}

static void	philo_routine(t_data *data, int ph)
{
	int	right_f;

	right_f = (ph + 1) % data->nb;
	pthread_mutex_lock(&data->forks[ph]);
	print(data, ph, "has taken a fork");
	pthread_mutex_lock(&data->forks[right_f]);
	print(data, ph, "has taken a fork"); 
	pthread_mutex_lock(&data->last_meals_mx[ph]);
	data->last_meals[ph] = get_current_time() - data->st_time;
	print(data, ph, "is eating");
	if (data->philo_meals != 0)
		data->total_meals[ph]++;
	pthread_mutex_unlock(&data->last_meals_mx[ph]);
	if (is_simulation_end(data, right_f, ph))
		return ;
	ft_usleep(data->tm_eat);
	print(data, ph, "is sleeping");
	pthread_mutex_unlock(&data->forks[right_f]);
	pthread_mutex_unlock(&data->forks[ph]);
	ft_usleep(data->tm_sleep);
	print(data, ph, "is thinking");
	if (data->nb % 2 && data->tm_sleep >= data->tm_eat)
		ft_usleep(data->tm_sleep);	
}

static void	wait_init(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->nb_mx);
		if (data->init_nb >= data->nb)
		{
			pthread_mutex_unlock(&data->nb_mx);
			return ;
		}
		pthread_mutex_unlock(&data->nb_mx);
		usleep(50);
	}
}

void	*routine(void *arg)
{
	t_data	*data;
	int		right_f;
	int		ph;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->nb_mx);
	ph = data->init_nb;
	data->init_nb++;
	pthread_mutex_unlock(&data->nb_mx);
	wait_init(data);
	ft_usleep((data->tm_eat / 2) * (ph % 2));
	while (1)
	{
		if (ph == data->nb - 1)
			last_philo_routine(data, ph);
		else
			philo_routine(data, ph);
		pthread_mutex_lock(&data->nb_mx);
		if (data->is_end)
			break ;
		pthread_mutex_unlock(&data->nb_mx);
	}
	pthread_mutex_unlock(&data->nb_mx);
	return (NULL);
}
