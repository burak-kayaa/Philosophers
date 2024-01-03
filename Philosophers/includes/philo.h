/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burkaya <burkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:03:31 by burkaya           #+#    #+#             */
/*   Updated: 2024/01/03 13:33:12 by burkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include "pthread.h"
# include "unistd.h"
# include "sys/time.h"
# include "time.h"

# define ARGERR "Wrong usage: ./philo philo_count time_dead\
time_eat time_sleep [time_eat_count]."
# define ARRWRONG "You must give numbers."
# define FORKS "has taken forks"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_philo
{
	int				p_id;
	pthread_t		philo;
	long long		e_count;
	struct s_data	*data;
	long long		pres_time;
	int				control;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	t_philo			*id;
	pthread_t		phio;
	long long		p_count;
	long long		dead_t;
	long long		eat_t;
	long long		sleep_t;
	long long		eat_count_t;
	int				tf_die;
	pthread_mutex_t	*printing;
	pthread_mutex_t	*tf_dies;
	int				err;
	long long		start_t;
	pthread_mutex_t	*forks;
}	t_data;

int			null_struct(t_data *data);
long long	get_time(void);
int			ft_isdigit(char *str);
void		init_struct(t_data *data, int i);
void		check_control(t_philo *philo);
void		*routine(void *arg);
int			ft_atoi(const char *s);
void		print_situation(t_philo *philo, long long time_s, char *str);
int			dead_check_philo(t_philo *philo);

#endif