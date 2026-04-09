/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:23:29 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/09 14:34:00 by anis             ###   ########.fr       */
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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notepme;
	int				death;
	pthread_mutex_t	**tab_of_mutex;
	pthread_mutex_t	mutex_log;
	pthread_t		thread_supervisor; // pour verifier que tout le monde est vivant, ou si un philo est ☠️
}	t_params;

typedef struct s_philo
{
	int	id;
	int	time_lm; // heure du dernier repas
	pthread_mutex_t	*right_fork; // mutex qu'on lock pour prendre la fourchette
	pthread_mutex_t	*left_fork;
	pthread_mutex_t last_meal; // mutex pour lire et ecrire l'heure du dernier repas
	pthread_t	*thread;
	t_params	*params;
}	t_philo;

int		ft_isdigit(int c);
int		test_num(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	init_struct(t_params *params, int argc, char **argv);
void	init_mutex(t_params *params);
void	init_philo(t_params *params, t_philo **philos);
void	init_forks(t_philo *philo, t_params *params);

#endif