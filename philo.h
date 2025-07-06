/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:25:24 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/06 09:25:25 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	pthread_t		*phs;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*last_meals_mx;
	long			*last_meals;
	int				*total_meals;
	pthread_t		manger;
	pthread_mutex_t	nb_mx;
	pthread_mutex_t	write_mx;
	long			st_time;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				philo_meals;
	int				init_nb;
	int				nb;
	int				is_end;
}					t_data;

long				custom_atoi(char *str);
void				ft_putstr_fd(char *str, int fd);
int					ft_clean(t_data *data, int status);
int					ft_malloc(t_data **data, int ac, int nb);
int					ft_setup(t_data *data, int ac, char **av);
int					ft_free(t_data *data, int status);
void				*routine(void *arg);
void				*monitor(void *arg);
void				print(t_data *data, int ph, char *state);
void				ft_usleep(long time);
long				get_current_time(void);

#endif