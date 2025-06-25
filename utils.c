#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;
    long            curr_time;

	gettimeofday(&time, NULL);
    curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (curr_time);
}

void     ft_usleep(long time)
{
    long    st_time;

    st_time = get_current_time();
    while (get_current_time() - st_time < time)
    {
        usleep(500);
    }
}

void    print(t_data *data,int ph,char *state)
{
    long time;

    pthread_mutex_lock(&data->write_mx);
    if (data->is_end)
    {
        pthread_mutex_unlock(&data->write_mx);
        return;
    }
    time = get_current_time() - data->st_time;
    printf("%ld %d %s\n",time,ph,state);
    pthread_mutex_unlock(&data->write_mx);
}

