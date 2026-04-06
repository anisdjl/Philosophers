/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:23:29 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/06 17:28:25 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include "gc.h"

typedef struct s_philo t_philo;

typedef struct s_params
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;
	pthread_mutex_t	**tab_of_mutex;
	pthread_mutex_t	mutex_log;
	pthread_t		thread_supervisor;
	t_philo			**tab_of_philo;
}	t_params;

typedef struct s_philo
{
	int	id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t	*thread;
	t_params	*params;
}	t_philo;

int		ft_isdigit(int c);
int		test_num(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	init_struct(t_params *params, int argc, char **argv);
void	init_mutex(t_params *params);
void	init_philo(t_params *params);

#endif