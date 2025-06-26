#include "philo.h"


static int eat_all_meals(t_data *data)
{
    int  i;

    i = 0;
    while (i < data->nb)
    {
        pthread_mutex_lock(&data->last_meals_mx[i]);
        if (data->total_meals[i] < data->philo_meals)
        {
            pthread_mutex_unlock(&data->last_meals_mx[i]);
            return(0);
        }
        pthread_mutex_unlock(&data->last_meals_mx[i]);
        i++;
    }
    pthread_mutex_lock(&data->nb_mx);
    data->is_end = 1;
    pthread_mutex_unlock(&data->nb_mx);
    return(1);
}

void    *stop_simulation(t_data *data,int ph)
{
    long    curr_time;

    pthread_mutex_unlock(&data->last_meals_mx[ph]);
    pthread_mutex_lock(&data->nb_mx);
    data->is_end = 1;
    pthread_mutex_unlock(&data->nb_mx);
    curr_time = get_current_time() - data->st_time;
    printf("%ld %d died\n",curr_time,ph);
    if (data->nb == 1)
        pthread_mutex_unlock(&data->forks[ph]);
    return (NULL);
}

void    *monitor(void *arg)
{
    t_data      *data;
    long        curr_time;
    int         i;

    data = (t_data *)arg;
    while (1)
    {
        //usleep(1000);
        i = 0;
        while (i < data->nb)
        {
            pthread_mutex_lock(&data->last_meals_mx[i]);
            curr_time = get_current_time() - data->st_time;
            if (curr_time - data->last_meals[i] > (long)data->tm_die)
                return (stop_simulation(data,i));
            pthread_mutex_unlock(&data->last_meals_mx[i]);
            i++;
        }
        if (data->philo_meals != 0 && eat_all_meals(data))
            break ;
    }
    return (NULL);
}
