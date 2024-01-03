/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:10:52 by burkaya           #+#    #+#             */
/*   Updated: 2024/01/03 11:28:16 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_control(t_philo *philo)
{
	pthread_mutex_lock(philo->data->tf_dies);
	philo->control = philo->data->tf_die;
	pthread_mutex_unlock(philo->data->tf_dies);
}

void	*one_philo(void *arg)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->r_fork);
	print_situation(philo, get_start_time() - philo->data->start_t, FORKS);
	time = get_start_time() - philo->data->start_t;
	while (dead_check_philo(philo))
	{
		if (philo->data->dead_t == get_start_time() - 
			philo->data->start_t - time)
		{
			printf("%lld %d died\n", get_start_time() - \
				philo->data->start_t, philo->p_id);
			pthread_mutex_unlock(philo->r_fork);
			return (0);
		}
		usleep(50);
	}
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static int	ft_thread(t_data *data)
{
	long long	i;

	i = -1;
	while (++i < data->p_count)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->p_count)
	{
		init_struct(data, i);
		data->id[i].r_fork = &data->forks[i];
		data->id[i].l_fork = &data->forks[((i + 1) % data->p_count)];
	}
	i = -1;
	while (++i < data->p_count)
	{
		data->err = pthread_create(&data->id[i].philo, NULL, 
				routine, &data->id[i]);
		if (data->err)
			return (i);
	}
	i = -1;
	while (++i < data->p_count)
		pthread_join(data->id[i].philo, NULL);
	return (0);
}

static int	argc_checker(t_data *data, char **argv, int argc)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(ft_isdigit(argv[i])))
			return (0);
		i++;
	}
	data->p_count = ft_atoi(argv[1]);
	data->dead_t = ft_atoi(argv[2]);
	data->eat_t = ft_atoi(argv[3]);
	data->sleep_t = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_count_t = ft_atoi(argv[5]);
	data->id = malloc(sizeof(t_philo) * data->p_count);
	if (!data->id)
		return (free(data->printing), free(data->tf_dies), free(data), 0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->p_count);
	if (!data->forks)
		return (free(data->printing), free(data->tf_dies), 
			free(data->id), free(data), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("%s\n", ARGERR), 0);
	data = malloc(sizeof(t_data));
	if (!data || !null_struct(data) || !argc_checker(data, argv, argc))
		return (0);
	if (data->p_count > 1)
		ft_thread(data);
	else
	{
		pthread_mutex_init(&data->forks[0], NULL);
		init_struct(data, 0);
		data->id[0].r_fork = &data->forks[0];
		data->err = pthread_create(&data->id[0].philo,
				NULL, one_philo, &data->id[0]);
		if (data->err)
			return (0);
		pthread_join(data->id[0].philo, NULL);
	}
	pthread_mutex_destroy(data->printing);
	pthread_mutex_destroy(data->forks);
	return (free(data->printing), free(data->tf_dies), free(data->id), 
		free(data->forks), free(data), 1);
}
