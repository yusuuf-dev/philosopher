#include "philo.h"

static void philo_routine(t_data *data,int ph)
{
    int     right_f;

    right_f = (ph + 1) % data->nb;
    pthread_mutex_lock(&data->forks[ph]);
    print(data,ph,"has taken a fork");
    pthread_mutex_lock(&data->forks[right_f]);
    print(data,ph,"has taken a fork");
    pthread_mutex_lock(&data->last_meals_mx[ph]);
    data->last_meals[ph] = get_current_time() - data->st_time;
    print(data,ph,"is eating");
    if (data->philo_meals != 0)
        data->total_meals[ph]++;
    pthread_mutex_unlock(&data->last_meals_mx[ph]);
    ft_usleep(data->tm_eat);
    print(data,ph,"is sleeping");
    pthread_mutex_unlock(&data->forks[right_f]);    
    pthread_mutex_unlock(&data->forks[ph]);
    ft_usleep(data->tm_sleep);
    print(data,ph,"is thinking");
}

void    *routine(void *arg)
{
    t_data          *data;
    int             right_f;
    int             ph;

    data = (t_data *)arg;
    pthread_mutex_lock(&data->nb_mx);
    ph = data->init_nb;
    data->init_nb++;
    pthread_mutex_unlock(&data->nb_mx);
    pthread_mutex_lock(&data->wait_mx);
    while (1)
    {
        pthread_mutex_lock(&data->nb_mx);
        if (data->init_nb >= data->nb)
        {
            pthread_mutex_unlock(&data->nb_mx);
            pthread_mutex_unlock(&data->wait_mx);
            break;
        }
        pthread_mutex_unlock(&data->nb_mx);
    }
    ft_usleep(1);
    ft_usleep(1 * (ph % 2));
    while (!data->is_end)
    {
       philo_routine(data,ph);
    }
    return (NULL);
}
