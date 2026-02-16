/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:25:04 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/16 12:38:48 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_params	*params;

	if (argc < 5 || argc > 6)
		return (0);
	if (!test_num(argc, argv))
		return (0);
	params = malloc(sizeof(t_params));
	init_struct(params, argc, argv);
}

void	init_struct(t_params *params, int argc, char **argv)
{
	params->philo = malloc(sizeof(t_philo));
	if (!params->philo)
		free(params);
	params->nb_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->notepme = ft_atoi(argv[5]);
	else
		params->notepme = 0;
}
