/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:25:04 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/06 17:28:44 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_params	*params;

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
	
	wait_all_threads(params);
	ft_free_all_malloc();
	//init_philo(params);
}

void	init_philo(t_params *params)
{
	int y;

	y = 0;
	params->tab_of_philo = ft_malloc(1, sizeof(pthread_t *) * params->nb_philo);
	while (y < params->nb_philo)
	{
		params->tab_of_philo[y] = ft_malloc(1, sizeof(pthread_t));
		pthread_create(params->tab_of_philo[y]->thread, NULL, NULL, NULL);
		params->tab_of_philo[y]->id = y + 1;
		// init_forks(params, y);
		y++;
	}
}

void	init_mutex(t_params *params)
{
	int	y;
	
	y = 0;
	params->tab_of_mutex = ft_malloc(1, sizeof(pthread_mutex_t *) * (params->nb_philo));
	while (y < params->nb_philo)
	{
		params->tab_of_mutex[y] = ft_malloc(1, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(params->tab_of_mutex[y], NULL) != 0)
		{
			ft_free_all_malloc();
			exit(EXIT_FAILURE);
		}
		y++;
	}
	pthread_mutex_init(&params->mutex_log, NULL);
}

void	init_struct(t_params *params, int argc, char **argv)
{
	params->nb_philo = ft_atoi(argv[1]);
	printf("%d\n", params->nb_philo);
	params->time_to_die = ft_atoi(argv[2]);
	printf("%d\n", params->time_to_die);
	params->time_to_eat = ft_atoi(argv[3]);
	printf("%d\n", params->time_to_eat);
	params->time_to_sleep = ft_atoi(argv[4]);
	printf("%d\n", params->time_to_sleep);
	if (argc == 6)
		params->notepme = ft_atoi(argv[5]);
	else
		params->notepme = -1; // je le mets a -1 comme ca je pourrais chcecker si il y a un notepme sino nje n'arrete pas la simulation 
}
