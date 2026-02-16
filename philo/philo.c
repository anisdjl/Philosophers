/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:25:04 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/16 10:17:28 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_params	*params;

	if (argc < 5 || argc > 6)
		return (0);
	params = malloc(sizeof(t_params));
	init_struct(params, argc, argv);
}

void	init_struct(t_params *params, int argc, char **argv)
{
	params->philo = malloc(sizeof(t_philo));
	if (!params->philo)
		free(params);
	params->nb_philo = argv[1];
	params->time_to_die = argv[2];
	params->time_to_eat = argv[3];
	params->time_to_sleep = argv[4];
	if (argc == 6)
		params->notepme = argv[5];
	else
		params->notepme = 0;
}
