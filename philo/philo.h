/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:23:29 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/19 12:29:50 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include "gc.h"

typedef struct s_philo t_philo;

typedef struct s_params
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				notepme;
	int				death;
	long			start_time;
	t_philo			*tab_of_philo;
	pthread_mutex_t	read_flag_death;
	pthread_mutex_t	*tab_of_mutex;
	pthread_mutex_t	mutex_log;
	pthread_t		thread_supervisor;
}	t_params;

typedef struct s_philo
{
	int	id;
	long	time_lm;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t last_meal;
	pthread_t	thread;
	t_params	*params;
	int			number_of_meal;
}	t_philo;

int		ft_isdigit(int c);
int		test_num(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	init_struct(t_params *params, int argc, char **argv);
void	init_mutex(t_params *params);
void	init_philo(t_params *params, t_philo **philos);
void	init_forks(t_philo *philo, t_params *params);
void	*supervisor(void *arg);
long	get_time_of_day_ms(void);
long	time_last_meal(int time, t_philo *philo);
int		ft_usleep(int time_to_sleep, t_philo *philo);
void	launch_threads(t_philo *philo, t_params *params);
void	*algo(void *arg);
int		not_dead(t_philo *philo, t_params *params);
void	wait_all_threads(t_params *params, t_philo *philo);
void	update_last_meal(t_philo *philo);
int		odd_philos(t_philo *philo);
int		even_philos(t_philo *philo);
void	writer(t_philo *philo, int n);

#endif