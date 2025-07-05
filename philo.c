#include "philo.h"

static int	check_args(int ac, char **av)
{
	long	check;
	int		i;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Enter 4 or 5 arguments\n", 2);
		return (1);
	}
	if (ac >= 5)
	{
		i = 1;
		while (i < ac)
		{
			check = custom_atoi(av[i]);
			if (i == 5 && check == 0)
				return (1);
			if (check == -1 || check == 0)
			{
				ft_putstr_fd("Enter valid argument\n", 2);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

static int	run_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		if (pthread_create(&data->phs[i], NULL, routine, data) != 0)
			return (ft_clean(data, 2));
		i++;
	}
	if (pthread_create(&data->manger, NULL, monitor, data) != 0)
		return (ft_clean(data, 2));
	i = 0;
	while (i < data->nb)
	{
		if (pthread_join(data->phs[i], NULL) != 0)
			return (ft_clean(data, 3));
		i++;
	}
	if (pthread_join(data->manger, NULL))
		return (ft_clean(data, 3));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (check_args(ac, av))
		return (1);
	if (ft_malloc(&data, ac, custom_atoi(av[1])))
		return (1);
	if (ft_setup(data, ac, av))
		return (1);
	// usleep(1000);
	if (run_threads(data))
		return (1);
	ft_clean(data, 0);
	return (0);
}
