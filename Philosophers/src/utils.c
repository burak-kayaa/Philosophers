/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:15:11 by burkaya           #+#    #+#             */
/*   Updated: 2024/01/03 13:32:57 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *s)
{
	int		i;
	long	back;
	int		np;

	back = 0;
	np = 1;
	i = 0;
	while ((s[i] <= 13 && s[i] >= 9) || s[i] == 32)
		i++;
	if (s[i] == 43 || s[i] == 45)
	{
		if (s[i] == 45)
			np *= -1;
		i++;
	}
	while (s[i] >= 48 && s[i] <= 57)
	{
		back = back * 10 + (s[i] - 48) * np;
		if (back > 2147483647)
			return (-1);
		if (back < -2147483648)
			return (0);
		i++;
	}
	return ((int)back);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (!(str[i] >= 48 && str[i] <= 57))
		{
			printf("%s | Error ARG : %s\n", ARRWRONG, str);
			return (0);
		}
		i++;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000)); 
}

void	init_struct(t_data *data, int i)
{
	data->id[i].p_id = i + 1;
	data->id[i].data = data;
	data->id[i].pres_time = get_time() - data->start_t;
	data->id[i].e_count = 0;
	data->id[i].control = 0;
}

int	null_struct(t_data *data)
{
	data->p_count = 0;
	data->dead_t = 0;
	data->eat_t = 0;
	data->sleep_t = 0;
	data->eat_count_t = -1;
	data->tf_die = 0;
	data->start_t = get_time();
	data->printing = malloc(sizeof(pthread_mutex_t));
	if (!data->printing)
		return (free(data), 0);
	data->tf_dies = malloc(sizeof(pthread_mutex_t));
	if (!data->tf_dies)
		return (free(data->printing), free(data), 0);
	pthread_mutex_init(data->printing, NULL);
	pthread_mutex_init(data->tf_dies, NULL);
	return (1);
}
