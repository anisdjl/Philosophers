/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:25:04 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/20 16:28:29 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_params	*params;
	t_philo		*philos;

	philos = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of args\n");
		return (0);
	}
	if (!test_num(argc, argv))
		return (0);
	params = ft_malloc(1, sizeof(t_params));
	init_struct(params, argc, argv);
	init_mutex(params);
	init_philo(params, &philos);
	launch_threads(philos, params);
	wait_all_threads(params, philos);
	ft_free_all_malloc();
	return (0);
}

void	init_philo(t_params *params, t_philo **philos)
{
	int		y;
	long	start_time;

	y = 0;
	start_time = get_time_of_day_ms();
	*philos = ft_malloc(1, sizeof(t_philo) * params->nb_philo);
	while (y < params->nb_philo)
	{
		(*philos)[y].id = y + 1;
		init_forks((*philos + y), params);
		(*philos)[y].params = params;
		if (pthread_mutex_init(&(*philos)[y].last_meal, NULL) != 0)
		{
			ft_free_all_malloc();
			exit(EXIT_FAILURE);
		}
		(*philos)[y].number_of_meal = 0;
		(*philos)[y].time_lm = start_time;
		y++;
	}
	params->tab_of_philo = *philos;
}

void	init_forks(t_philo *philo, t_params *params)
{
	philo->left_fork = &params->tab_of_mutex[philo->id - 1];
	philo->right_fork = &params->tab_of_mutex[(philo->id) % params->nb_philo];
}

void	init_mutex(t_params *params)
{
	int	y;

	y = 0;
	params->tab_of_mutex = ft_malloc(1, sizeof(pthread_mutex_t)
			* (params->nb_philo));
	while (y < params->nb_philo)
	{
		if (pthread_mutex_init(&params->tab_of_mutex[y], NULL) != 0)
		{
			ft_free_all_malloc();
			exit(EXIT_FAILURE);
		}
		y++;
	}
	if (pthread_mutex_init(&params->mutex_log, NULL) != 0
		|| pthread_mutex_init(&params->mutex_nbom, NULL) != 0)
	{
		ft_free_all_malloc();
		exit(EXIT_FAILURE);
	}
	if (pthread_mutex_init(&params->read_flag_death, NULL) != 0)
	{
		ft_free_all_malloc();
		exit(EXIT_FAILURE);
	}
}

void	init_struct(t_params *params, int argc, char **argv)
{
	params->nb_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->notepme = ft_atoi(argv[5]);
	else
		params->notepme = -1;
	params->start_time = get_time_of_day_ms();
	params->death = 0;
}
