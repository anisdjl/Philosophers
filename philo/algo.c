/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:18:33 by anis              #+#    #+#             */
/*   Updated: 2026/04/09 15:23:12 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_philo **philo, t_params *params)
{
	int	y;

	y = 0;

	while (y < params->nb_philo)
	{
		pthread_create(&philo[y], NULL, &algo, philo[y]);
		y++;
	}
}

void	algo(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		if (!not_dead(philo, philo->params))
			break ;
		pthread_mutex_lock(philo->left_fork);
		usleep(philo->params->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		usleep(900);
	}
	return ; // pas sur de laisser ca ici
}

int	not_dead(t_philo *philo, t_params *params)
{
	
}

int	time_calculator(t_philo *philo)
{
	struct timeval	start;

	
}
